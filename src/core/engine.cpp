#include "folk/core/engine.hpp"
#include "../window/window_manager.hpp"
#include "engine_singleton.hpp"

namespace Folk::Engine {

void exit() 
{
    ENGINE.exit();
}

void setWindowTitle(const char* text) 
{
    ENGINE.window.setWindowTitle(text);
}

void setPerformanceMetricsEnabled(bool value)
{
    ENGINE.perf_monitor.setVisibility(value);
}

void setMinFrameTime(double time)
{
    std::chrono::duration<double> seconds {time};
    ENGINE.min_frame_time = std::chrono::duration_cast<std::chrono::nanoseconds>(seconds);
}

} // namespace folk::engine