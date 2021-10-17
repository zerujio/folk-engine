#ifndef FOLK_UTILS__THREAD_SAFE_COUNTER_HPP
#define FOLK_UTILS__THREAD_SAFE_COUNTER_HPP

/// \~spanish \brief Tipo entero protegido con mutex.
/// \~english \brief Mutex protected integer counter.
/**
 * \~spanish \param T un tipo entero.
 * \~english \param T integer type
*/
template <typename T>
class ThreadSafeCounter {
public:

    /// \~spanish \brief Construye un contador, inicializado en cero.
    /// \~english \brief Construct counter initialized to zero.
    ThreadSafeCounter() : count(0) {}

    /// \~spanish \brief Construye un contador con el valor dado.
    /// \~english \brief Construct counter initialized to given value.
    /**
     * \~spanish \param n valor inicial.
     * \~english \param n initial value.
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

    /// \~spanish \brief Casteo al tipo T retorna el número entero subyacente.
    /// \~english \brief Cast to type T returns the underlying integer.
    operator T() const {
        return count;
    }

private:
    T count {0};
    std::mutex mtx {};
};

#endif // FOLK_UTILS__THREAD_SAFE_COUNTER_HPP