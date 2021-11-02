#ifndef FOLK_UTILS__PERFORMANCE_MONITOR_HPP
#define FOLK_UTILS__PERFORMANCE_MONITOR_HPP

#include <string>
#include <vector>
#include <chrono>

namespace Folk
{

class PerformanceMonitor {

public:
    /// Determines if the monitor is rendered.
    bool visible {false};

    /// Start timer for specified item
    void start(int);

    /// Stop timer for specified item
    void stop(int);

    /// Add a new item to the monitor
    int addItem(const char*);

private:
    using Delta = std::chrono::duration<double, std::milli>;
    using Clock = std::chrono::steady_clock;

    struct Item {
        std::string name;
        Delta delta;
        Clock::time_point start;

        Item(const char* str) 
            : name(str), start(Clock::now()), delta(0)
        {}
    };
    std::vector<Item> items;

    void draw();
    friend class Renderer;
};

} // namespace Folk


#endif // FOLK_UTILS__PERFORMANCE_MONITOR_HPP