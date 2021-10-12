#include "module.hpp"
#include "../core/engine_singleton.hpp"
#include "folk/core/error.hpp"

#include <exception>

namespace folk {

void ExceptionModule::handle()
{
    try {
        std::rethrow_exception(std::current_exception());
    
    } catch (CriticalEngineError &e) {
        ENGINE.out << "CriticalEngineError: " << e.what() << "\n";
        ENGINE.exit();

    } catch (std::exception &e) {
        ENGINE.out << e.what();
    
    } catch (...) {
        ENGINE.out << "Caught unexpected exception!\n";
        ENGINE.exit();
    }
}

} // namespace folk