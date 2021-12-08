#ifndef FOLK_CORE__EXCEPTION_HANDLER_HPP
#define FOLK_CORE__EXCEPTION_HANDLER_HPP

#include "../utils/processing_queue.hpp"
#include "../utils/raii_thread.hpp"

#include <exception>
#include <functional>

namespace Folk {

class ExceptionHandler final {

public:

    static const char* name() {return "exception_handler";}

    ExceptionHandler();
    ~ExceptionHandler();
    
    /// Handle the current exception.
    /**
     * This function is meant to be called inside the catch part of a 
     * try-catch.
    */
    void handleException();

    /// Throw exception of the given type.
    /**
     * Equivalent to:
     * ```
     * try {
     *   throw Exception(args...);
     * } catch (...) {
     *   handler.handle();
     * }
     * ```
    */
    template<class Exception, class... Args>
    void throwException(Args&&... args) {
        queue.enqueue(std::make_exception_ptr(Exception(std::forward<Args>(args)...)));
    }

private:
    using QueueT = ProcessingQueue<std::exception_ptr>;

    QueueT queue {};
    RAIIThread handler_thread {&ExceptionHandler::handlerRoutine, this};

    static QueueT s_queue;

    void handlerRoutine();
};

} // namespace folk

#endif // FOLK_CORE__EXCEPTION_HANDLER_HPP