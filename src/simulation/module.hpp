#ifndef FOLK_SIMULATION__MODULE_HPP
#define FOLK_SIMULATION__MODULE_HPP

#include "../engine/engine_module.hpp"

#include <iostream>

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(SimulationModule) {
    void onStartUp() {std::cout << "Simulation module up!\n";}
    void onShutDown() {std::cout << "Simulation module down!\n";}
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Simulation")
};

} // namespace folk

#endif//FOLK_SIMULATION__MODULE_HPP