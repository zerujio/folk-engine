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

// utils
#include "../utils/singleton.hpp"
#include "../utils/processing_queue.hpp"
#include "../utils/coroutine.hpp"
#include "../utils/delta_clock.hpp"

#include "../debug/performance_monitor.hpp"

#include "main.hpp"

namespace Folk
{

/// Singleton class to access aplication level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {

public:
    PerformanceMonitor perf_monitor;

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

    bool exit_flag {false};

    DeltaClock frame_clock {};

    static const uint umodule_count = 3;

    const std::array<UpdateableModule*, umodule_count> updateable_modules {
        &window, &scene, &render
    };
    
    EngineSingleton();
    ~EngineSingleton();

    void mainLoop();

    friend int ::main();
};

#define ENGINE EngineSingleton::instance()

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_SINGLETON_HPP