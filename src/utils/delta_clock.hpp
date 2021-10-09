#ifndef FOLK_UTILS__DELTA_TIMER_HPP
#define FOLK_UTILS__DELTA_TIMER_HPP

#include <chrono>

namespace folk {

/// Utility class for mesuring frame times (deltaT)
class DeltaClock {
public:
    using clock = std::chrono::steady_clock;
    using nanoseconds = std::chrono::nanoseconds;

    /// Default constructor.
    /** 
     * Time for the first frame begins immediately upon construction. maxDelta 
     * defaults to half a second.
     */
    DeltaClock() = default;

    /// Construct a clock with the given value for maxDelta.
    /**
     * @param max_delta an std::chrono::duration for maxDelta.
     * @see maxDelta()
     * @see setMaxDelta()
     */
    DeltaClock(std::chrono::nanoseconds max_delta);

    /// raw time delta for last frame.
    /**
     * @param <T> std::chrono::duration instance representing the time unit
     * @return unclamped time delta for last frame.
     */
    template<typename T = nanoseconds>
    inline T rawDelta();

    /// time delta for last frame, clamped to the range [0, maxDelta].
    /**
     * @param <T> std::chrono::duration instance representing the time unit
     * @return clamped time delta for last frame.
     */
    template<typename T = nanoseconds>
    inline T delta();

    /// Mark the end of current frame and the start of a new one.
    /**
     * A time delta is the time passed between two consecutive invocations of 
     * this function. The current frame is the one that began with the last
     * call to this function and will end with the next.
     */
    void click();

    /// set max value to be returned by [delta()](@ref delta)
    /**
     * @param dt std::chrono duration
     * @see delta()
     */
    void setMaxDelta(std::chrono::nanoseconds dt);

    /// Maximum value [delta()](@ref delta) may return.
    /**
     * @param <T> an std::chrono::duration type
     */
    template <typename T = nanoseconds>
    inline T maxDelta();

private:
    nanoseconds _last_delta {1};
    nanoseconds _clamped_last_delta {1};
    nanoseconds _max_delta {std::chrono::milliseconds(500)};
    clock::time_point _initial_time {clock::now()};
};

template<typename T>
T DeltaClock::rawDelta() {
    return std::chrono::duration_cast<T>(_last_delta);
}

template<typename T>
T DeltaClock::delta() {
    return std::chrono::duration_cast<T>(_clamped_last_delta);
}

template<typename T>
T DeltaClock::maxDelta() {
    return std::chrono::duration_cast<T>(_max_delta);
}

}//namespace folk

#endif//FOLK_UTILS__DELTA_TIMER_HPP