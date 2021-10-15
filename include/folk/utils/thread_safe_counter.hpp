#ifndef FOLK_UTILS__THREAD_SAFE_COUNTER_HPP
#define FOLK_UTILS__THREAD_SAFE_COUNTER_HPP

/// Mutex protected integer counter
/**
 * @param T integer type
*/
template <typename T>
class ThreadSafeCounter {
public:
    /// Construct counter initialized to zero.
    ThreadSafeCounter() : count(0) {}

    /// Construct counter initialized to given value.
    /**
     * @param n initial value.
    */
    ThreadSafeCounter(T n) : count(n) {}

    ThreadSafeCounter(ThreadSafeCounter const& cntr)
    : ThreadSafeCounter(cntr.count)
    {}

    ThreadSafeCounter& operator++() {
        std::lock_guard lk(mtx);
        ++count;
        return *this;
    }

    T operator++(int) {
        std::lock_guard lk(mtx);
        return count++;
    }

    ThreadSafeCounter& operator--() {
        std::lock_guard lk(mtx);
        --count;
        return *this;
    }

    T operator--(int) {
        std::lock_guard lk(mtx);
        return count--;
    }

    /// Cast to type T returns the underlying integer.
    operator T() const {
        return count;
    }

private:
    T count {0};
    std::mutex mtx {};
};

#endif // FOLK_UTILS__THREAD_SAFE_COUNTER_HPP