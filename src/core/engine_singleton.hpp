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

/// Singleton class to manage application level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {

    friend class Engine;

    /// Exit flag: set to true to signal the Engine to exit (return from mainLoop).
    bool exit_flag {false};

    DeltaClock frame_clock {};
    DeltaClock::nanoseconds min_frame_time {0};

    /// Log thread
    LogInitializer log_init {};
    LogThread log_thread {};

    /// Performance monitor
    PerformanceMonitor perf_monitor;

    /// Exception handling
    ExceptionHandler m_exception_handler {ExceptionHandler::CallbackArg<&EngineSingleton::exit>, this};

    /// Window manager
    WindowManager window {};

    /// Render module
    Renderer render {m_exception_handler, window};

    /// Audio module
    AudioManager audio {m_exception_handler};

    /// Scene module
    SceneManager scene {};

    /// Input manager
    InputManager input_manager {m_exception_handler, window};

    void update(std::chrono::nanoseconds);

public:

    // Functions
    /// Signal the engine to exit.
    void exit() noexcept;

    /// output stream
    std::ostream& out {std::cout};

    /// error outpout stream
    std::ostream& errout {std::cerr};

    explicit EngineSingleton(LogLevel level);
    ~EngineSingleton();

    void mainLoop() noexcept;
};

#define ENGINE EngineSingleton::instance()

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_SINGLETON_HPP