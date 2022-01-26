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
 * @brief Return type for error checking functions.
 * @tparam What a type such that an std::logic_error or std::runtime_error may be initialized with it.
 */
template<class What>
struct CLibraryErrorDescriptor final {
    /// `true` if no error occurred.
    bool ok;
    /// If an error occurred, contains a description of it.
    What what;
};

/**
 * @brief Wrapper for C library calls.
 * @tparam errorCheck An error checking function. It should return a CLibraryErrorDescriptor.
 * @tparam Function A function pointer type.
 * @tparam Args Types of function parameters.
 * @param file name of source file.
 * @param line source line.
 * @param calling_function name of calling function.
 * @param function The function to call.
 * @param args The arguments to pass to the function.
 * @return The result of `function_ptr(args...);`
 */
template<auto errorCheck, class Function, class... Args>
auto libraryCall(const char* file, int line, const char* calling_function, Function function, Args&&... args)
{
    static_assert(std::is_invocable_v<Function, Args...>, "Invalid argument types!");

    constexpr bool returns_void {std::is_void_v<decltype(function(args...))>};

    if constexpr (returns_void) {
        function(args...);
        auto check = errorCheck();
        if (!check.ok)
            throw CLibraryError(check.what, file, line, calling_function);
    } else {
        auto value = function(args...);
        auto check = errorCheck();
        if (!check.ok)
            throw CLibraryError(check.what, file, line, calling_function);
        return value;
    }
}

} // namespace Folk

#endif //SRC_UTILS__LIBRARY_CALL_HPP
