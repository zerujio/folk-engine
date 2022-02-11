//
// Created by sergio on 25-01-22.
//

#ifndef SRC_UTILS__LIBRARY_CALL_HPP
#define SRC_UTILS__LIBRARY_CALL_HPP

#include "folk/error.hpp"
#include "folk/debug.hpp"
#include "folk/utils/source_location.hpp"
#include "folk/log.hpp"

#include <type_traits>
#include <functional>
#include <optional>

namespace Folk {

using std::experimental::source_location;

struct LibraryError : public Error {
    using Error::Error;
};

/**
 * @brief Creates callables that invoke C library functions and perform error checking (if enabled).
 * @tparam Exception An exception object. It should inherit from Folk::Error (or CriticalError) and a similar constructor.
 * @tparam getError An error checking function. Generally, it should be a wrapper for a function like glGetError().
 * @tparam ErrorArgs Arguments to forward to the error checking function.
 *
 * The signature for the error checking function is: R (*) (ErrorArgs...), where R is either:
 * - a type implicitly convertible to bool, such that it evaluates to true if an error occurred and false otherwise,
 * AND the type is such that an object of type Exception may be initialized from it. Or,
 * - std::optional<T>, where T is a type such that an object of type Exception may be initialized from it. The return
 * value should contain an object only if an error occurred.
 *
 * The constructor of Folk::Error is Error(StringType what, source_location = source_location::current()) in debug builds
 * and Error(StringType what) on release builds.
 */
template<class Exception, auto getError, class... ErrorArgs>
class LibCall final {
public:

    LibCall() = delete;

    template<class Return, class... Args>
    using Function = Return (*) (Args...);

    /**
     * @brief Call a library function and, only on DEBUG builds, perform error checking.
     * @tparam Return return type of the function.
     * @tparam Args argument types of the function.
     * @param function a function pointer.
     * @param error_args arguments to pass to the error checking function.
     * @return On DEBUG builds: a lambda that calls @p function and throws an exception if an error occurred. On
     * RELEASE builds: @p function.
     *
     * The intended usage of this function is like so:
     * ```
     * LibCallDispatcher call {getError};
     * // ...
     * auto value = call(someFunction)(arg1, arg2, arg3);
     * ```
     *
     * This is a "fast" call because error checking should effectively be optimized out on release builds.
     */
    template<class Return, class... Args>
    static constexpr auto fast(Function<Return, Args...> function, ErrorArgs... error_args) noexcept {
        if constexpr (c_debug_build) {
            // DEBUG
            // get location : true
            // throwing     : true
            return lambda<true, true>(function, error_args...);
        } else {
            // RELEASE
            return function;
        }
    }

    /**
     * @brief Call a library function and, only on DEBUG builds, perform error checking.
     * @tparam Return return type of the function.
     * @tparam Args Argument types of the function.
     * @param function The function to call.
     * @param error_args Arguments to pass to the error checking function.
     * @return On debug builds: a lambda that calls @p function and writes to the Log if an error occurred. On release
     * builds: @p function.
     *
     * This is a "fast" call because error checking should effectively be optimized out on release builds.
     */
    template<class Return, class... Args>
    static constexpr auto fastNoExcept(Function<Return, Args...> function, ErrorArgs... error_args) noexcept {
        if constexpr (c_debug_build) {
            // DEBUG
            // get location : true
            // throwing     : false
            return lambda<true, false>(function, error_args...);
        } else {
            // RELEASE
            return function;
        }
    }

    /**
     * @brief Call a library function and always perform error checking.
     * @tparam Return return type of the function.
     * @tparam Args argument types of the function.
     * @param function the function to call.
     * @param error_args arguments to pass to the error checking function.
     * @return A lambda that calls @p function and throws an exception if an error occurred.
     *
     * This is a "slow" call because error checking is always performed, not only on debug builds.
     */
    template<class Return, class... Args>
    static constexpr auto slow(Function<Return, Args...> function, ErrorArgs... error_args) noexcept {
        if constexpr (c_debug_build) {
            // DEBUG
            // capture location : true
            // throwing         : true
            return lambda<true, true>(function, error_args...);
        } else {
            // RELEASE
            // capture location : false
            // throwing         : true
            return lambda<false, true>(function, error_args...);
        }
    }

    /**
     * @brief Call a library function and always perform error checking.
     * @tparam Return return type of the function.
     * @tparam Args argument types of the function.
     * @param function the function to call.
     * @param error_args arguments to pass to the error checking function.
     * @return A lambda that calls @p function and writes to the Log if an error occurred.
     *
     * This is a "slow" call because error checking is always performed, not only on debug builds.
     */
    template<class Return, class... Args>
    static constexpr auto slowNoExcept(Function<Return, Args...> function, ErrorArgs... error_args) noexcept {
        if constexpr (c_debug_build) {
            // DEBUG
            // capture location : true
            // throwing         : false
            return lambda<true, false>(function, error_args...);
        } else {
            // RELEASE
            // capture location : false
            // throwing         : false
            return lambda<false, false>(function, error_args...);
        }
    }

private:

    template<class R>
    static constexpr R getErrorReturnValue(R error) {
        return error;
    }

    template<class R>
    static constexpr const R& getErrorReturnValue(const std::optional<R>& an_optional) {
        return *an_optional;
    }

    template<bool Throwing>
    static constexpr void checkErrors(ErrorArgs... error_args) noexcept(!Throwing)
    {
        auto error = getError(error_args...);
        if (error) {
            if constexpr (Throwing)
                throw Exception(getErrorReturnValue(error));
            else
                Log::error() << getErrorReturnValue(error) << '\n';
        }
    }

    template<bool Throwing>
    static constexpr void checkErrors(const source_location loc, ErrorArgs... error_args) noexcept(!Throwing)
    {
        auto error = getError(error_args...);
        if (error) {
            if constexpr (Throwing)
                throw Exception(getErrorReturnValue(error), loc);
            else
                Log::error() << loc << " : " << getErrorReturnValue(error) << '\n';
        }
    }

    template<bool Throwing, class Return, class... Args>
    static constexpr auto callAndCheckErrors(ErrorArgs... error_args, Function<Return, Args...> function, Args... args)
    noexcept(!Throwing)
    {
        if constexpr (std::is_void_v<Return>) {
            function(args...);
            checkErrors<Throwing>(error_args...);
        } else {
            auto value = function(args...);
            checkErrors<Throwing>(error_args...);
            return value;
        }
    }

    template<bool Throwing, class Return, class... Args>
    static constexpr auto callAndCheckErrors(const source_location loc, ErrorArgs... error_args,
                                             Function<Return, Args...> function, Args... args)
    noexcept(!Throwing)
    {
        if constexpr(std::is_void_v<Return>) {
            function(args...);
            checkErrors<Throwing>(loc, error_args...);
            Log::trace() << loc << "\n";
        } else {
            auto value = function(args...);
            checkErrors<Throwing>(loc, error_args...);
            Log::trace() << loc << "\n";
            return value;
        }
    }

    template<bool CaptureLocation, bool Throwing, class Return, class... Args>
    static constexpr auto lambda(Function<Return, Args...> function, ErrorArgs... error_args) noexcept {

        if constexpr (CaptureLocation) {
            return [function, error_args...] (Args... args, source_location loc = source_location::current())
            noexcept (!Throwing) {
                getError(error_args...); // clear error state;
                return callAndCheckErrors<Throwing>(loc, error_args..., function, args...);
            };

        } else {
            return [function, error_args...] (Args... args)
            noexcept (!Throwing) {
                getError(error_args...);
                return callAndCheckErrors<Throwing>(error_args..., function, args...);
            };
        }
    }
};

} // namespace Folk

#endif //SRC_UTILS__LIBRARY_CALL_HPP
