#ifndef FOLK_ENGINE__ENGINE_SINGLETON_HPP
#define FOLK_ENGINE__ENGINE_SINGLETON_HPP

#include <array>
#include <ostream>
#include <iostream>
#include <exception>
#include <thread>

#include "folk/scene.hpp"

// modules
#include "../render/renderer.hpp"
#include "../audio/audio_manager.hpp"
#include "../window/window_manager.hpp"
#include "../scene/scene_manager.hpp"
#include "../input/input_manager.hpp"
#include "exception_handler.hpp"

// utils
#include "../utils/singleton.hpp"
#include "../utils/processing_queue.hpp"
#include "../utils/delta_clock.hpp"

#include "../debug/performance_monitor.hpp"

#include "log_thread.hpp"
#include "main.hpp"

namespace Folk
{

/// Singleton class to access application level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {

    friend class Engine;

    LogInitializer log_init {};
    LogThread log_thread {};

    PerformanceMonitor perf_monitor;

public:
    // Engine

    /// Exception handling
    ExceptionHandler exception {};

    /// Window module
    WindowManager window {};

    /// Render module
    Renderer render {exception, window};

    /// Audio module
    AudioManager audio {};

    /// Scene module
    SceneManager scene {};

    /// Input manager
    InputManager input_manager {exception};

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
    
    explicit EngineSingleton(LogLevel level);
    ~EngineSingleton();

    void mainLoop() noexcept;
    void update(std::chrono::nanoseconds);

    friend int ::main(int, char**);
};

#define ENGINE EngineSingleton::instance()

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_SINGLETON_HPP