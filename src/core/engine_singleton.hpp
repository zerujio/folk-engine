#ifndef FOLK_ENGINE__ENGINE_SINGLETON_HPP
#define FOLK_ENGINE__ENGINE_SINGLETON_HPP

#include <array>
#include <ostream>
#include <iostream>
#include <exception>
#include <thread>

#include "folk/scene/scene.hpp"

// modules
#include "../render/module.hpp"
#include "../audio/module.hpp"
#include "../simulation/module.hpp"
#include "../window/module.hpp"
#include "../scene/module.hpp"
#include "../exception/module.hpp"

#include "../utils/singleton.hpp"
#include "../utils/processing_queue.hpp"
#include "../utils/coroutine.hpp"
#include "../utils/delta_clock.hpp"
#include "main.hpp"

namespace Folk
{

/// Singleton class to access aplication level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {

public:
    // Engine modules

    /// Exception handling module
    ExceptionModule exception {};

    /// Window module
    WindowModule window {};

    /// Render module
    RenderModule render {};

    /// Audio module
    AudioModule audio {};

    /// simulation module
    SimulationModule simulation {};

    /// Scene module
    SceneModule scene {};

    /// Signal the engine to exit.
    void exit() noexcept;

    /// output stream
    std::ostream& out {std::cout};

    /// error outpout stream
    std::ostream& errout {std::cerr}; 

private:
    EngineSingleton();
    ~EngineSingleton();

    void mainLoop();

    bool exit_flag {false};

    DeltaClock frame_clock {};

    friend int ::main();
};

#define ENGINE EngineSingleton::instance()

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_SINGLETON_HPP