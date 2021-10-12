#include "module.hpp"
#include "../core/engine_singleton.hpp"
#include "folk/core/error.hpp"

#include <exception>

namespace folk {

ExceptionModule::ExceptionModule() {}

ExceptionModule::~ExceptionModule() {
    queue.stopProcessing();
}

void ExceptionModule::handle()
{
    queue.enqueue(std::current_exception());
}

void ExceptionModule::handlerRoutine() 
{
    queue.processLoop(
        [] (std::exception_ptr ptr) {
            try {
                std::rethrow_exception(ptr);
        
            } catch (CriticalEngineError &e) {
                ENGINE.out << "CriticalEngineError: " << e.what() << "\n";
                ENGINE.exit();

            } catch (std::exception &e) {
                ENGINE.out << "RuntimeException: " << e.what() << "\n";
        
            } catch (...) {
                ENGINE.out << "Caught unexpected exception!\n";
                ENGINE.exit();
            }
        }
    );
}

} // namespace folk