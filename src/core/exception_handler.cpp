#include "exception_handler.hpp"
#include "engine_singleton.hpp"

#include "folk/error.hpp"

#include <exception>

namespace Folk {

ExceptionHandler::ExceptionHandler() {}

ExceptionHandler::~ExceptionHandler() {
    queue.stopProcessing();
}

void ExceptionHandler::handleException()
{
    queue.enqueue(std::current_exception());
}

void ExceptionHandler::handlerRoutine() 
{
    queue.processLoop(
        [] (std::exception_ptr &ptr) {
            try {
                std::rethrow_exception(ptr);
        
            } catch (CriticalError &e) {
                Log::error() << e << "\n";
                ENGINE.exit();
            
            } catch (RuntimeError &e) {
                Log::error() << e << "\n";

            } catch (std::exception &e) {
                Log::error()
                    << "Exception: " << e.what() << "\n";
        
            } catch (...) {
                Log::error() << "Caught unexpected exception!\n";
                ENGINE.exit();
            }
        }
    );
}

} // namespace folk