#ifndef FOLK_UTILS__COROUTINE_HPP
#define FOLK_UTILS__COROUTINE_HPP

#include <functional>
#include <thread>

namespace folk {

/// A RAII wrapper for a thread.
/** 
 * Thread begins execution when the object is constructed, and is joined when 
 * the object is destroyed.
*/
class Coroutine {
public:
    template<typename Function, typename ... Args>
    Coroutine(Function&& f, Args&&... args) 
        : thread(std::forward<Function>(f), std::forward<Args>(args)...) {}

    ~Coroutine() 
    {
        thread.join();
    }

private:
    std::thread thread;
};

}//namespace folk

#endif//FOLK_UTILS__COROUTINE_HPP