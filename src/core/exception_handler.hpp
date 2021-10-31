#ifndef FOLK_CORE__EXCEPTION_HANDLER_HPP
#define FOLK_CORE__EXCEPTION_HANDLER_HPP

#include "module.hpp"

#include "../utils/processing_queue.hpp"
#include "../utils/raii_thread.hpp"

#include <exception>

namespace Folk {

FOLK_ENGINE_MODULE(ExceptionHandler) {

public:

    const char* name() const override {return "exception_handler";}

    ExceptionHandler();
    ~ExceptionHandler();
    
    /// Handle the current exception.
    /**
     * This function is meant to be called inside the catch part of a 
     * try-catch.
    */
    void handle();

private:
    using QueueT = ProcessingQueue<std::exception_ptr>;

    QueueT queue {};
    RAIIThread handler_thread {&ExceptionHandler::handlerRoutine, this};

    void handlerRoutine();
};

} // namespace folk

#endif // FOLK_CORE__EXCEPTION_HANDLER_HPP