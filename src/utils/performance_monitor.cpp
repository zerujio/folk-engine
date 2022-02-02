#include "performance_monitor.hpp"

#include "folk/window/window_manager.hpp"

#include "../core/engine.hpp"

#include "folk/error.hpp"

namespace Folk
{

void PerformanceMonitor::start(int k) {
    items[k].start = Clock::now();
}

void PerformanceMonitor::stop(int k) {
    items[k].item.delta = Clock::now() - items[k].start;
}

void PerformanceMonitor::setVisibility(bool v) noexcept {
    visible = v;
}

bool PerformanceMonitor::getVisibility() const noexcept {
    return visible;
}

const PerformanceMonitor::Item& PerformanceMonitor::getItem(int k) const {
    if (k >= items.size())
        throw FOLK_RUNTIME_ERROR("Item index out of range");
    
    return items[k].item;
}

int PerformanceMonitor::addItem(const char* text) {
    items.emplace_back(text);
    return items.size() - 1;
}

std::size_t PerformanceMonitor::size() const noexcept {
    return items.size();
}

void PerformanceMonitor::clear() noexcept {
    items.clear();
}

} // namespace Folk
