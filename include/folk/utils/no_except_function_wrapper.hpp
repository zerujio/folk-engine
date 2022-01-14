//
// Created by sergio on 13-01-22.
//

#ifndef INCLUDE_FOLK_UTILS__NO_EXCEPT_FUNCTION_WRAPPER_HPP
#define INCLUDE_FOLK_UTILS__NO_EXCEPT_FUNCTION_WRAPPER_HPP

#include <exception>
#include <functional>

namespace Folk {

/**
 * @brief A simple object that contains either a value or an exception pointer.
 * @tparam ValueType The type of the contained object.
 */
template<class ValueType>
class ValueOrException final {

    union {
        ValueType m_value;
        std::exception_ptr m_exception_ptr;
    };
    bool m_is_value;

public:
    explicit ValueOrException(std::enable_if_t<std::is_copy_constructible_v<ValueType>, const ValueType&> value)
    : m_is_value(true), m_value(value)
    {}

    explicit ValueOrException(std::enable_if_t<std::is_move_constructible_v<ValueType>, ValueType&&> value)
    : m_is_value(true), m_value(std::move(value))
    {}

    explicit ValueOrException(std::exception_ptr ptr)
    : m_is_value(false), m_exception_ptr(std::move(ptr))
    {}

    /// Return true if this object contains a value (i.e. is not a an exception).
    operator bool() const {
        return m_is_value;
    }

    /**
     * @brief Read only access to the contained value.
     * @return a const reference to the contained value.
     */
    [[nodiscard]] const ValueType& value() {
        return m_value;
    }

    /**
     * @brief Move access to the contained value.
     * @return an rvalue reference to the contained value.
     */
    [[nodiscard]] ValueType&& extractValue() {
        return std::move(m_value);
    }

    /**
     * @brief Get the contained exception pointer.
     */
    [[nodiscard]] std::exception_ptr exceptionPtr() const {
        return m_exception_ptr;
    }
};

/**
 * @brief Wraps a function in a `try-catch` block.
 * @tparam Function The function to wrap.
 * @tparam ReturnType The return type of the function.
 * @tparam ParamTypes The parameter types of the function.
 * @param args The arguments to pass to the function.
 * @return an std::exception pointer to the possibly caught exception (null if the function returned normally).
 */
template<auto Function, class ReturnType, class... ParamTypes>
std::enable_if_t<std::is_void_v<ReturnType>, std::exception_ptr>
NoExceptFunctionWrapper(ParamTypes&&... args) noexcept
try {
    Function(std::forward<ParamTypes>(args)...);
    return {};
} catch (...) {
    return std::current_exception();
}

/**
 * @brief Wraps a function in a `try-catch` block.
 * @tparam Function The function to wrap.
 * @tparam ReturnType The return type of the function.
 * @tparam ParamTypes The parameter types of the function.
 * @param args The arguments to pass to the function.
 * @return a ValueOrException<ReturnType> object.
 */
template<auto Function, class ReturnType, class... ParamTypes>
std::enable_if_t<!std::is_void_v<ReturnType>, ValueOrException<ReturnType>>
NoExceptFunctionWrapper(ParamTypes&&... args) noexcept
try {
    return {Function(std::forward<ParamTypes>(args)...)};
} catch (...) {
    return {std::current_exception()};
}

} // namespace Folk

#endif //INCLUDE_FOLK_UTILS__NO_EXCEPT_FUNCTION_WRAPPER_HPP
