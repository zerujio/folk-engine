#ifndef FOLK_SIMULATION__MODULE_HPP
#define FOLK_SIMULATION__MODULE_HPP

#include <iostream>

#include "../core/module.hpp"

namespace Folk {

FOLK_ENGINE_MODULE(SimulationModule) {

public:
    const char* name() const override {return "simulation";}

private:
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