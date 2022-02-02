//
// Created by sergio on 01-02-22.
//

#include "engine.hpp"

#include "folk/core/game.hpp"

#include "folk/utils/exception_handler.hpp"
#include "../utils/scoped_initializer.hpp"

#include "../window/windowing_system.hpp"

#include "folk/input.hpp"

#include "../audio/audio_manager.hpp"

#include "../render/renderer.hpp"

#include "folk/folk.hpp"

namespace Folk {

template<class T>
class ScopedAssignment final {

public:
    ScopedAssignment(T& variable, T new_value) : var(variable), old_value(variable) {
        var = new_value;
    }

    ~ScopedAssignment() {
        var = old_value;
    }

private:
    T& var;
    T old_value;
};

DeltaClock::nanoseconds Engine::min_frame_time {};
const WindowManager* Engine::game_window_ptr {nullptr};
bool Engine::exit_flag {false};

void Engine::main(LogLevel level) {

    // Exception handler
    ExceptionHandler exception_handler {ExceptionHandler::CallbackArg<Game::exit>};

    // initialize log thread
    ScopedInitializer<Log> log_initializer{};

    // create main window
    ScopedInitializer<Folk::WindowingSystem> window_init {};
    const WindowManager game_window {"Unnamed Folk Engine application"};
    game_window.setCloseCallback<Game::exit>();
    ScopedAssignment ptr_assignment {game_window_ptr, &game_window};

    // Input handling
    InputEventQueue input_queue{};
    ScopedInitializer<Input> input_initializer{InputManager(game_window), input_queue};

    // Audio
    AudioManager audio_manager {exception_handler};

    // Renderer
    Renderer::setContext(game_window);

    // Scene manager
    SceneManager scene_manager{};

    // Allow user to change engine settings.
    try {
        engineInit();
    } catch (...) {
        exception_handler.catchException();
        throw std::runtime_error("engineInit() error");
    }

    // initialize scene
    try {
        sceneInit(scene_manager.scene());
    } catch (...) {
        exception_handler.catchException();
        throw std::runtime_error("sceneInit() error");
    }

    // Performance monitor
    PerformanceMonitor perf_monitor {};

    // delta clock
    DeltaClock delta_clock {};

    while (!exit_flag) {
        delta_clock.click();

        auto delta = delta_clock.delta();
        if (delta < min_frame_time) {
            auto ti = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(min_frame_time - delta);
            delta += std::chrono::steady_clock::now() - ti;
        }

        // frame start
        auto frame_time_id = perf_monitor.addItem("Frame time");

        pollEvents(perf_monitor, exception_handler);
        updateScene(perf_monitor, exception_handler, scene_manager, input_queue, delta);
        updateAudio(perf_monitor, exception_handler, audio_manager, scene_manager, delta);
        drawFrame(perf_monitor, exception_handler, scene_manager, delta);

        // frame end
        perf_monitor.stop(frame_time_id);

        Renderer::drawPerfMon(perf_monitor, delta);
        perf_monitor.clear();
        log_initializer.wakeUp(); // print log buffer to console
    }
}

void Engine::pollEvents(PerformanceMonitor &perf_monitor, const ExceptionHandler& exception_handler) noexcept
try {
    auto monitor_id = perf_monitor.addItem("Event polling (windowing system)");
    WindowingSystem::pollEvents();
    perf_monitor.stop(monitor_id);
} catch (...) {
    exception_handler.catchException();
    return;
}

void Engine::updateScene(PerformanceMonitor &perf_monitor, const ExceptionHandler &exception_handler,
                         SceneManager &scene_manager, InputEventQueue &event_queue,
                         DeltaClock::seconds_double delta) noexcept
{
    auto id = perf_monitor.addItem("Scene update");
    scene_manager.updateScene(event_queue, exception_handler, delta);
    perf_monitor.stop(id);
}

void Engine::updateAudio(PerformanceMonitor &perf_monitor, const ExceptionHandler &exception_handler,
                         AudioManager &audio_manager, SceneManager& scene_manager,
                         DeltaClock::seconds_double delta) noexcept
{
    auto id = perf_monitor.addItem("Audio update");
    audio_manager.update(exception_handler, scene_manager, delta);
    perf_monitor.stop(id);
}

void Engine::drawFrame(PerformanceMonitor &perf_monitor, const ExceptionHandler &exception_handler,
                       SceneManager &scene_manager, DeltaClock::seconds_double delta) noexcept
try
{
    auto id = perf_monitor.addItem("Renderer");
    Renderer::drawFrame(scene_manager, delta);
    perf_monitor.stop(id);
}
catch (...)
{
    Log::write(LogLevel::Error) << "An error occurred during draw phase:\n";
    exception_handler.catchException();
    return;
}

} // namespace Folk