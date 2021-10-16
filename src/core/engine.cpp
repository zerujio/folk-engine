#include "folk/core/engine.hpp"
#include "../window/module.hpp"
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
    ENGINE.perf_monitor.visible = value;
}

void setMinFrameTime(double time)
{
    ENGINE.min_frame_time = UpdateListener::Delta(time);
}

} // namespace folk::engine