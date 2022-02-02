#ifndef SRC_FOLK_ENGINE__ENGINE_SINGLETON_HPP
#define SRC_FOLK_ENGINE__ENGINE_SINGLETON_HPP

#include "folk/log.hpp"

#include "folk/window/window_manager.hpp"

#include "../utils/delta_clock.hpp"
#include "../utils/performance_monitor.hpp"
#include "../scene/scene_manager.hpp"

#include "../audio/audio_manager.hpp"

namespace Folk
{

struct Engine final {

    friend class Game;

public:

    Engine() = delete;

    static void main(LogLevel level);

private:

    static bool exit_flag;
    static const WindowManager* game_window_ptr;
    static DeltaClock::nanoseconds min_frame_time;

    static void pollEvents(PerformanceMonitor& perf_monitor, const ExceptionHandler& exception_handler) noexcept;
    static void updateScene(PerformanceMonitor &perf_monitor, const ExceptionHandler &exception_handler,
                            SceneManager &scene_manager, InputEventQueue &event_queue,
                            DeltaClock::seconds_double delta) noexcept;
    static void updateAudio(PerformanceMonitor& perf_monitor, const ExceptionHandler& exception_handler,
                            AudioManager& audio_manager, SceneManager& scene_manager,
                            DeltaClock::seconds_double delta) noexcept;
    static void drawFrame(PerformanceMonitor& perf_monitor, const ExceptionHandler& exception_handler,
                          SceneManager& scene_manager, DeltaClock::seconds_double delta) noexcept;

};

} // namespace Folk::Engine

#endif//SRC_FOLK_ENGINE__ENGINE_SINGLETON_HPP