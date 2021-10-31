#include "exception_handler.hpp"
#include "engine_singleton.hpp"

#include "folk/core/error.hpp"

#include <exception>

namespace Folk {

ExceptionHandler::ExceptionHandler() {}

ExceptionHandler::~ExceptionHandler() {
    queue.stopProcessing();
}

void ExceptionHandler::handle()
{
    queue.enqueue(std::current_exception());
}

void ExceptionHandler::handlerRoutine() 
{
    queue.processLoop(
        [] (std::exception_ptr &ptr) {
            try {
                std::rethrow_exception(ptr);
        
            } catch (CriticalEngineError &e) {
                ENGINE.log.begin(Log::Level::ERROR) << "Critical error: " 
                                                    << e.what() << "\n";
                ENGINE.exit();

            } catch (std::exception &e) {
                ENGINE.log.begin(Log::Level::ERROR) << "Exception: " 
                                                    << e.what() << "\n";
        
            } catch (...) {
                ENGINE.log.begin(Log::Level::ERROR)
                           << "Caught unexpected exception!\n";
                ENGINE.exit();
            }
        }
    );
}

} // namespace folk