#ifndef SRC_FOLK_ENGINE__ENGINE_SINGLETON_HPP
#define SRC_FOLK_ENGINE__ENGINE_SINGLETON_HPP

#include <array>
#include <ostream>
#include <iostream>
#include <exception>
#include <thread>

// log
#include "log_thread.hpp"

// exception handling
#include "folk/core/exception_handler.hpp"

// renderer
#include "../render/renderer.hpp"

// audio
#include "../audio/audio_manager.hpp"

// windowing
#include "../window/window_manager.hpp"
#include "../window/windowing_system.hpp"

// input
#include "folk/input.hpp"
#include "../input/input_manager.hpp"
#include "../input/input_event_queue.hpp"
#include "../input/input_initializer.hpp"

// scene management
#include "folk/scene.hpp"
#include "../scene/scene_manager.hpp"
#include "../debug/performance_monitor.hpp"

// utils
#include "../utils/singleton.hpp"
#include "../utils/delta_clock.hpp"

#include "main.hpp"

namespace Folk
{

#define ENGINE EngineSingleton::instance()

/// Singleton class to manage application level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {

    friend class Engine;

    /// Exit flag: set to true to signal the Engine to exit (return from mainLoop).
    bool exit_flag {false};

    /// Frame rate management
    DeltaClock frame_clock {};
    DeltaClock::nanoseconds min_frame_time {0};

    /// Log thread
    LogInitializer log_init {};
    LogThread log_thread {};

    /// Performance monitor
    PerformanceMonitor perf_monitor {};

    /// Exception handler
    ExceptionHandler m_exception_handler {ExceptionHandler::CallbackArg<&EngineSingleton::exit>};

    /// Windowing
    WindowingSystem::ScopedInitializer windowing_system_init {};
    WindowManager m_game_window {"Unnamed Folk Engine application"};

    /// Input handling
    InputEventQueue m_input_queue {};
    Input::ScopedInitializer m_input_init {InputManager(m_game_window), m_input_queue};

    /// Render module
    Renderer render {m_exception_handler, m_game_window};

    /// Audio module
    AudioManager audio {m_exception_handler};

    /// Scene module
    SceneManager scene {};

    void update(std::chrono::nanoseconds);

public:
    explicit EngineSingleton(LogLevel level);
    ~EngineSingleton();

    /// Change current scene. Argument will be left in a moved from state.
    void changeScene(Scene&&);

    void mainLoop() noexcept;

    /// Signal the engine to exit.
    static void exit() noexcept;
};

} // namespace folk

#endif//SRC_FOLK_ENGINE__ENGINE_SINGLETON_HPP