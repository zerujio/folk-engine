#ifndef FOLK_UTILS__PERFORMANCE_MONITOR_HPP
#define FOLK_UTILS__PERFORMANCE_MONITOR_HPP

#include <string>
#include <vector>
#include <chrono>

namespace Folk
{

class PerformanceMonitor {

public:
    using Delta = std::chrono::duration<double, std::milli>;

    /// Start timer for specified item
    void start(int);

    /// Stop timer for specified item
    void stop(int);

    /// Add a new item to the monitor. Count is immediately started.
    /**
     * \param text Text description of the item. String must remain valid for the
     *             lifetime of the item.
     * \return the index needed to call \ref start() and \ref stop() on this item
     */
    int addItem(const char* label);

    struct Item {
        const char* label;
        Delta delta;
    };
    const Item& getItem(int) const;

    void setVisibility(bool value) noexcept;

    bool getVisibility() const noexcept;

    std::size_t size() const noexcept;

    void clear() noexcept;

private:
    /// Determines if the monitor is rendered.
    bool visible {false};

    using Clock = std::chrono::steady_clock;

    struct _Item {
        Item item;
        Clock::time_point start;

        _Item(const char* str) : item{str, Delta::zero()}, start(Clock::now()) {}
    };
    std::vector<_Item> items;
};

} // namespace Folk


#endif // FOLK_UTILS__PERFORMANCE_MONITOR_HPP