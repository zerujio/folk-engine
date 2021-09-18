#include "engine_module.hpp"

namespace folk {

void EngineModule::startUp() {
    if (initialized)
        throw EngineRuntimeError(name() + ": module is already up, can't start up.");

    onStartUp();
    initialized = true;
}

void EngineModule::shutDown() {
    if (!initialized) 
        throw EngineRuntimeError(name() + ": module is not up, can't shut down.");
    
    onShutDown();
    initialized = false;
}

} // namespace folk