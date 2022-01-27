//
// Created by sergio on 25-01-22.
//

#ifndef SRC_UTILS__LIBRARY_CALL_HPP
#define SRC_UTILS__LIBRARY_CALL_HPP

#include "folk/error.hpp"

#include <type_traits>

namespace Folk {

/// Exception thrown when a library error occurs.
struct CLibraryError : public RuntimeError {
    using RuntimeError::RuntimeError;
};

/**
 * @brief Wrapper for C library calls.
 * @tparam getError An error checking function. It should return an std::optional containing a descriptive message in
 * case of an error and be empty otherwise.
 * @tparam function A function to call.
 * @tparam Args Types of function parameters.
 * @param file name of source file.
 * @param line source line.
 * @param calling_function name of calling function.
 * @param args The arguments to pass to the function.
 * @return The result of `function_ptr(args...);`
 */
template<auto getError, auto function, class... Args>
auto libraryCall(const char* file, int line, const char* calling_function, Args&&... args)
{
    static_assert(std::is_invocable_v<decltype(function), Args...>, "Invalid argument types!");

    if constexpr (std::is_void_v<decltype(function(args...))>) {
        // void return type
        function(args...);
        auto error = getError();
        if (error)
            throw CLibraryError(*error, file, line, calling_function);

    } else {
        auto value = function(args...);
        auto error = getError();
        if (error)
            throw CLibraryError(*error, file, line, calling_function);
        return value;
    }
}

/// C library call wrapper with an error checking function that takes a single argument.
template<auto getError, class ErrorCheckArg, auto function, class... FunctionArgs>
auto libraryCall(const char* file, int line, const char* calling_function, ErrorCheckArg&& error_arg, FunctionArgs&&... args)
{
    static_assert(std::is_invocable_v<decltype(function), FunctionArgs...>, "Invalid function argument types.");
    static_assert(std::is_invocable_v<decltype(getError), ErrorCheckArg>, "Invalid error check function argument type.");

    if constexpr (std::is_void_v<decltype(function(args...))>) {
        // void return type
        function(args...);
        auto error = getError(error_arg);
        if (error)
            throw CLibraryError(*error, file, line, calling_function);
    } else {
        auto value = function(args...);
        auto error = getError(error_arg);
        if (error)
            throw CLibraryError(*error, file, line, calling_function);
        return value;
    }
}

#define FOLK_C_LIBRARY_CALL(errorCheck, function, ...)\
libraryCall<errorCheck, function>(__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)

#define FOLK_C_LIBRARY_CALL_ERR_ARG(errorCheck, error_arg, function, ...)\
libraryCall<errorCheck, function>(__FILE_, __LINE__, __PRETTY_FUNCTION__, err_arg, ##__VA_ARGS__)

} // namespace Folk

#endif //SRC_UTILS__LIBRARY_CALL_HPP
