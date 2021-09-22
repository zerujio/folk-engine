#ifndef FOLK_SIMULATION__MODULE_HPP
#define FOLK_SIMULATION__MODULE_HPP

#include "../engine/engine_module.hpp"

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(SimulationModule) {
    void onStartUp() {}
    void onShutDown() {}
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Simulation")
};

} // namespace folk

#endif//FOLK_SIMULATION__MODULE_HPP