#ifndef FOLK_EXCEPTION__MODULE_HPP
#define FOLK_EXCEPTION__MODULE_HPP

#include "../utils/singleton.hpp"
#include "../utils/processing_queue.hpp"
#include "../utils/coroutine.hpp"

#include <exception>

namespace Folk {

FOLK_SINGLETON_CLASS_FINAL(ExceptionModule) {

public:
    ExceptionModule();
    ~ExceptionModule();
    
    /// Handle the current exception.
    /**
     * This function is meant to be called inside the catch part of a 
     * try-catch.
    */
    void handle();

private:
    using QueueT = ProcessingQueue<std::exception_ptr>;

    QueueT queue {};
    Coroutine handler_thread {&ExceptionModule::handlerRoutine, this};

    void handlerRoutine();
};

} // namespace folk

#endif // FOLK_EXCEPTION__MODULE_HPP