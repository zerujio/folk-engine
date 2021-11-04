#include "performance_monitor.hpp"

#include "../render/common.hpp"

#include "../window/window_manager.hpp"

#include "../core/engine_singleton.hpp"

namespace Folk
{

void PerformanceMonitor::start(int k) {
    items[k].start = Clock::now();
}

void PerformanceMonitor::stop(int k) {
    items[k].delta = Clock::now() - items[k].start;
}

void PerformanceMonitor::setVisibility(bool v) {
    visible = v;
    bgfx::setDebug(visible ? BGFX_DEBUG_TEXT : BGFX_DEBUG_NONE);
}

void PerformanceMonitor::draw() {
    if (visible) {
        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 0, 0x0f, "Performance metrics:");

        int line = 1;
        for (auto const& item : items) {
            bgfx::dbgTextPrintf(0, line++, 0x0f, "%s: %fms", item.name.c_str(), item.delta.count());
        }
    }
}

/**
 * \param text Text description of the item.
 * \return the index needed to call \ref start() and \ref stop() on this item
 */
int PerformanceMonitor::addItem(const char* text) {
    items.emplace_back(text);
    return items.size() - 1;
}

} // namespace Folk
