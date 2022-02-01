#include "folk/folk.hpp"

#include "folk/core/engine.hpp"
#include "engine.hpp"

#include "folk/log.hpp"

#include "../utils/delta_clock.hpp"
#include "../utils/scoped_initializer.hpp"

#include "../debug/performance_monitor.hpp"

#include "../window/windowing_system.hpp"
#include "folk/window/window_manager.hpp"

#include "folk/input/input_event_queue.hpp"
#include "folk/input/input_manager.hpp"
#include "folk/input.hpp"

#include "../audio/audio_manager.hpp"

#include "../scene/scene_manager.hpp"

#include "../render/renderer.hpp"

namespace Folk::Engine {

bool exit_flag {false};

void exit() noexcept
{
    exit_flag = true;
}

void setPerformanceMetricsEnabled(bool value) {
    // empty
}

void setWindowTitle(const char* title) {

}

void main(LogLevel level) {

    // delta clock
    DeltaClock delta_clock {};
    DeltaClock::nanoseconds min_frame_time {0};

    // initialize log thread
    ScopedInitializer<Log> log_initializer {};

    // Performance monitor
    PerformanceMonitor perf_monitor {};

    // Exception handler
    ExceptionHandler m_exception_handler {ExceptionHandler::CallbackArg<exit>};

    // Windowing
    ScopedInitializer<Folk::WindowingSystem> window_init {};
    const WindowManager m_game_window {"Unnamed Folk Engine application"};

    // Input handling
    InputEventQueue m_input_queue {};
    ScopedInitializer<Input> input_initializer {InputManager(m_game_window), m_input_queue};

    // Audio module
    AudioManager audio {m_exception_handler};

    // Scene module
    SceneManager scene_manager {};

    // window close callback
    m_game_window.setCloseCallback<exit>();

    Renderer::setContext(m_game_window);

    // finish engine initialization.
    try {
        engineInit();
    } catch (...) {
        m_exception_handler.catchException();
        throw std::runtime_error("engineInit() error");
    }

    // initialize scene
    try {
        sceneInit(scene_manager.scene());

    } catch (...) {
        m_exception_handler.catchException();
        throw std::runtime_error("sceneInit() error");
    }

    while (!exit_flag) {
        delta_clock.click();

        auto delta = delta_clock.delta();
        if (delta < min_frame_time) {
            auto ti = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(min_frame_time - delta);
            delta += std::chrono::steady_clock::now() - ti;
        }

        // start frame
        auto frame_time_id = perf_monitor.addItem("Frame time");

        // update window / process input
        {
            auto monitor_id = perf_monitor.addItem("Event polling (windowing system)");
            WindowingSystem::pollEvents();
            perf_monitor.stop(monitor_id);
        }

        // update scene
        {
            auto id = perf_monitor.addItem("Scene update");
            scene_manager.updateScene(m_input_queue, m_exception_handler, delta);
            perf_monitor.stop(id);
        }

        // update audio
        {
            auto id = perf_monitor.addItem("Audio update");
            try {
                audio.update(m_exception_handler, scene_manager, delta);
            } catch (...) {
                Log::write(LogLevel::Warning)
                        << "An error occurred during audio processing phase:\n";
                m_exception_handler.catchException();
            }
            perf_monitor.stop(id);
        }

        // draw
        {
            auto id = perf_monitor.addItem("Renderer");
            try {
                Renderer::drawFrame(scene_manager, delta);
            } catch (...) {
                Log::write(LogLevel::Warning)
                        << "An error occurred during draw phase:\n";
                m_exception_handler.catchException();
            }
            perf_monitor.stop(id);
        }

        // end frame
        perf_monitor.stop(frame_time_id);

        // draw performance metrics
        Renderer::drawPerfMon(perf_monitor, delta);
        perf_monitor.clear();

        // flush log
        log_initializer.wakeUp();
    }
}

} // namespace folk