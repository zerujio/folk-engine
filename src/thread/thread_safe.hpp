#ifndef THREAD__THREAD_SAFE_HPP
#define THREAD__THREAD_SAFE_HPP

#include <mutex>

namespace folk::thread
{

// Base class for thread-safe objects.
class ThreadSafeObject {

public:
    void lock();
    void unlock();
    
private:
    std::mutex m {};
};

}//namespace folk::thread

#endif//THREAD__THREAD_SAFE_HPP