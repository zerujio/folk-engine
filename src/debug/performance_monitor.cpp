#include "performance_monitor.hpp"

#include "../render/common.hpp"

#include "../window/module.hpp"

#include "../core/engine_singleton.hpp"

#include <imgui.h>

namespace Folk
{

void PerformanceMonitor::start(int k) {
    items[k].start = Clock::now();
}

void PerformanceMonitor::stop(int k) {
    items[k].delta = Clock::now() - items[k].start;
}

void PerformanceMonitor::draw() {
    if (visible) {
        ImGui::Begin("Performance metrics", &visible);

        if (! ImGui::IsWindowCollapsed()) {
            for (Item item : items) {
                ImGui::Text("%s: %fms", item.name.c_str(), item.delta.count());
            }
        }

        ImGui::End();
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
