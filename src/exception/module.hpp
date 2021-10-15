#ifndef FOLK_EXCEPTION__MODULE_HPP
#define FOLK_EXCEPTION__MODULE_HPP

#include "../core/module.hpp"
#include "../utils/processing_queue.hpp"
#include "../utils/coroutine.hpp"

#include <exception>

namespace Folk {

FOLK_ENGINE_MODULE(ExceptionModule) {

public:

    const char* name() const override {return "exception_handler";}

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