#ifndef FOLK_UTILS__COROUTINE_HPP
#define FOLK_UTILS__COROUTINE_HPP

#include <functional>
#include <thread>

namespace Folk {

/// A RAII wrapper for a thread.
/** 
 * Thread begins execution when the object is constructed, and is joined when 
 * the object is destroyed.
*/
class RAIIThread {
public:
    template<typename Function, typename ... Args>
    RAIIThread(Function&& f, Args&&... args) 
        : thread(std::forward<Function>(f), std::forward<Args>(args)...) {}

    ~RAIIThread() 
    {
        thread.join();
    }

private:
    std::thread thread;
};

}//namespace folk

#endif//FOLK_UTILS__COROUTINE_HPP