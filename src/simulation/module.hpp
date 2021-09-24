#ifndef FOLK_SIMULATION__MODULE_HPP
#define FOLK_SIMULATION__MODULE_HPP

#include <iostream>
#include "../utils/singleton.hpp"

namespace folk {

FOLK_SINGLETON_CLASS_FINAL(SimulationModule) {
    friend class EngineSingleton;
    
    SimulationModule() {
        std::cout << "Simulation: initialized\n";
    }

    ~SimulationModule() {
        std::cout << "Simulation: finalized\n";
    }
};

} // namespace folk

#endif//FOLK_SIMULATION__MODULE_HPP