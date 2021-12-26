#include "folk/core/engine.hpp"
#include "../window/window_manager.hpp"
#include "engine_singleton.hpp"

namespace Folk{

void Engine::exit()
{
    ENGINE.exit();
}

void Engine::setWindowTitle(const char* text)
{
    ENGINE.window.setWindowTitle(text);
}

void Engine::setPerformanceMetricsEnabled(bool value)
{
    ENGINE.perf_monitor.setVisibility(value);
}

void Engine::setMinFrameTime(double time)
{
    std::chrono::duration<double> seconds {time};
    ENGINE.min_frame_time = std::chrono::duration_cast<std::chrono::nanoseconds>(seconds);
}

} // namespace folk::engine