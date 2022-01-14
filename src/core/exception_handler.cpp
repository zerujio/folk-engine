#include "folk/core/exception_handler.hpp"
#include "engine_singleton.hpp"

#include "folk/error.hpp"

#include <exception>

namespace Folk {

    void ExceptionHandler::onCritical() const
    try {
        if (m_critical_error_callback)
            m_critical_error_callback();
    } catch (...) {
        Log::error() << "Critical";
    }

void ExceptionHandler::handleException(const std::exception_ptr& exception_ptr) const
try {
    std::rethrow_exception(exception_ptr);

} catch (CriticalError &e) {
    Log::error() << e << "\n";
    onCritical();

} catch (RuntimeError &e) {
    Log::error() << e << "\n";

} catch (std::exception &e) {
    Log::error() << "Exception: " << e.what() << "\n";

} catch (...) {
    Log::error() << "Caught unexpected exception!\n";
    onCritical();
}

void ExceptionHandler::catchException() const {
    handleException(std::current_exception());
}

} // namespace folk