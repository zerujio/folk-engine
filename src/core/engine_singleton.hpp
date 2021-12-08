#ifndef FOLK_ENGINE__ENGINE_SINGLETON_HPP
#define FOLK_ENGINE__ENGINE_SINGLETON_HPP

#include <array>
#include <ostream>
#include <iostream>
#include <exception>
#include <thread>

#include "folk/scene/scene.hpp"

// modules
#include "../render/renderer.hpp"
#include "../audio/audio_manager.hpp"
#include "../window/window_manager.hpp"
#include "../scene/scene_manager.hpp"
#include "../input/input_manager.hpp"
#include "../debug/log.hpp"
#include "exception_handler.hpp"

// utils
#include "../utils/singleton.hpp"
#include "../utils/processing_queue.hpp"
#include "../utils/raii_thread.hpp"
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

    /// Logging
    Log log;

    /// Exception handling
    ExceptionHandler exception {};

    /// Window module
    WindowManager window {};

    /// Input manager
    InputManager input_manager {exception};

    /// Render module
    Renderer render {log, exception, window};

    /// Audio module
    AudioManager audio {};

    /// Scene module
    SceneManager scene {};

    // Functions
    /// Signal the engine to exit.
    void exit() noexcept;

    /// output stream
    std::ostream& out {std::cout};

    /// error outpout stream
    std::ostream& errout {std::cerr}; 

    DeltaClock::nanoseconds min_frame_time {0};

private:

    bool exit_flag {false};

    DeltaClock frame_clock {};
    
    EngineSingleton(Log::Level log_level);
    ~EngineSingleton();

    void mainLoop() noexcept;
    void update(std::chrono::nanoseconds);

    friend int ::main(int, char**);
};

#define ENGINE EngineSingleton::instance()

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_SINGLETON_HPP