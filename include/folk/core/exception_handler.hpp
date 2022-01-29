#ifndef FOLK_CORE__EXCEPTION_HANDLER_HPP
#define FOLK_CORE__EXCEPTION_HANDLER_HPP

#include "entt/entt.hpp"

#include <exception>
#include <functional>

namespace Folk {

class ExceptionHandler final {

    entt::delegate<void(void)> m_critical_error_callback {};

    void onCritical() const;

public:

    template<auto T>
    using CallbackArg_t = entt::connect_arg_t<T>;

    template<auto FunctionType>
    static CallbackArg_t<FunctionType> CallbackArg;

    ExceptionHandler() = default;

    template<auto FunctionType, class... Args>
    explicit ExceptionHandler(CallbackArg_t<FunctionType> callback_arg, Args&&... args)
    : m_critical_error_callback(callback_arg, std::forward<Args>(args)...)
    {}

    /// Set the function to be invoked whenever a critical error is handled.
    template<auto Function, class T>
    void setCriticalErrorCallback(T&& arg) {
        m_critical_error_callback.connect<Function>(arg);
    }
    
    /// Handle the current exception.
    /**
     * This function is meant to be called inside the catch part of a 
     * try-catch.
    */
    void catchException() const;

    /// Throw exception of the given type.
    /**
     * Semantically equivalent to:
     * ```
     * try {
     *   throw Exception(args...);
     * } catch (...) {
     *   handler.handle();
     * }
     * ```
    */
    template<class Exception, class... Args>
    void throwException(Args&&... args) const {
        handleException(std::make_exception_ptr(Exception(std::forward<Args>(args)...)));
    }

    void handleException(const std::exception_ptr&) const;
};

template<auto F>
ExceptionHandler::CallbackArg_t<F> ExceptionHandler::CallbackArg {entt::connect_arg<F>};

} // namespace folk

#endif // FOLK_CORE__EXCEPTION_HANDLER_HPP