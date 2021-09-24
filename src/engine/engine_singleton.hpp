#ifndef FOLK_ENGINE__ENGINE_SINGLETON_HPP
#define FOLK_ENGINE__ENGINE_SINGLETON_HPP

#include <array>
#include <ostream>
#include <iostream>

#include "folk/scene.hpp"
#include "../utils/singleton.hpp"
#include "../render/module.hpp"
#include "../audio/module.hpp"
#include "../simulation/module.hpp"
#include "../window/module.hpp"
#include "main.hpp"

namespace folk
{

// Singleton class to access aplication level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {

public:
    // Engine modules
    WindowModule window {};
    RenderModule render {};
    AudioModule audio {};
    SimulationModule simulation {};

    // signal the engine to exit
    void exit() noexcept;

private:
    EngineSingleton();
    ~EngineSingleton();

    std::ostream& out {std::cout};
    std::ostream& errout {std::cerr}; 
    Scene scene {};
    bool exit_flag {false};

    void mainLoop() noexcept;

    friend int ::main();
};

#define ENGINE EngineSingleton::instance()

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_SINGLETON_HPP