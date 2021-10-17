#ifndef FOLK_UTILS__CONCURRENT_QUEUE_HPP
#define FOLK_UTILS__CONCURRENT_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <utility>

namespace Folk {

/// Concurrent FIFO queue for consumer-producer style processing.
/**
 * \param T type of the object to be processed
*/
template<typename T>
class ProcessingQueue {

public:
    ~ProcessingQueue();

    /** Wake all processing threads and cause them to return. */
    void stopProcessing();

    /** Begin processing elements in queue in a loop. If the queue is empty, 
    execution of calling thread will be suspended until a new element is 
    inserted. Processing will continue until a call to stopProcessing is made, 
    or the ProcessingQueue is destroyed.
    
    If more than one thread is waiting for new elements, the order in which they
    are woken up is undefined. 
    
    Note that processLoop will return immediately if a call to stopProcessing is
    in course. */
    void processLoop(std::function<void(T)>);

    /** Push a new element to the back of the queue. */
    void enqueue(T);

    /** Construct in place a new element at the back of the queue. */
    template<typename... Args>
    decltype(auto) emplace(Args&&... args);

private:
    std::mutex mutex;
    std::condition_variable cond_element_enqueued;
    std::condition_variable cond_processor_returned;
    std::queue<T> queue;
    uint processor_threads {0};
    bool processing_active {true};

};

// Definitions
template<typename T>
ProcessingQueue<T>::~ProcessingQueue()
{
    stopProcessing();
}

template<typename T>
void ProcessingQueue<T>::stopProcessing()
{
    std::unique_lock lock(mutex);
    processing_active = false;

    cond_element_enqueued.notify_all();
    cond_processor_returned.wait(lock, [this]{return processor_threads == 0;});

    processing_active = true;
}

template<typename T>
void ProcessingQueue<T>::processLoop(std::function<void(T)> processing_routine)
{
    std::unique_lock lock(mutex);
    ++processor_threads;

    while(processing_active) 
    {
        while(!queue.empty()) {
            auto element = queue.front();
            queue.pop();

            lock.unlock();
            processing_routine(element);
            lock.lock();
        }

        cond_element_enqueued.wait(lock);
    }

    --processor_threads;
    lock.unlock();
    cond_processor_returned.notify_all();
}

template<typename T>
void ProcessingQueue<T>::enqueue(T element)
{
    {
        std::unique_lock lock(mutex);
        queue.push(element);
    }
    cond_element_enqueued.notify_one();
}

template<typename T>
template<typename... Args>
decltype(auto) ProcessingQueue<T>::emplace(Args&&... args)
{
    {
        std::unique_lock lock(mutex);
        queue.emplace(std::forward<Args>(args)...);
    }
    cond_element_enqueued.notify_one();
}

} // namespace folk

#endif//FOLK_UTILS__CONCURRENT_QUEUE_HPP