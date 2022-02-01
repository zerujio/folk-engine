//
// Created by sergio on 14-01-22.
//

#ifndef SRC_UTILS__SIMPLE_QUEUE_HPP
#define SRC_UTILS__SIMPLE_QUEUE_HPP

#include <vector>
#include <functional>

namespace Folk {

/**
 * @brief A simple implementation of a FIFO queue.
 * Designed to be used in a loop where the queue is filled and cleared on each iteration. Based on a std::vector instead
 * of a std::deque or std::list to avoid unnecessary dynamic memory allocations.
 *
 * Ideally used with plain data types, as the destructors of the objects in the queue might never be called.
 *
 * @tparam T Type of the elements of the queue.
 */
template<class T>
class SimpleQueue {
public:

    /// Construct an empty queue.
    SimpleQueue() = default;

    /**
     * @brief Construct an empty queue.
     * @param size initial size for the internal array.
     */
    explicit SimpleQueue(std::size_t size) {
        m_array.reserve(size);
    }

    /**
     * @brief Push an element into the queue.
     * @tparam Args Type of the constructor args.
     * @param args Arguments to construct the new element.
     */
    template<class... Args>
    void push(Args&&... args) {
        auto index = m_end++;

        if (index >= m_array.size())
            m_array.template emplace_back(std::forward<Args>(args)...);
        else
            m_array[index] = T(std::forward<Args>(args)...);
    }

    /// Read-only access to the first element of the queue.
    const T& peek() const {
        return m_array[m_begin];
    }

    /// Extract the first element of the queue. Behavior is undefined if the queue is empty.
    T pop() {
        auto index = m_begin++;
        if (empty()) {
            m_begin = 0;
            m_end = 0;
        }
        return m_array[index];
    }

    /// Check if the queue is empty.
    [[nodiscard]] constexpr bool empty() const {
        return m_begin >= m_end;
    }

    /**
     * @brief Apply a function to all queued elements.
     * If an exception occurs, the state of the queue will remain unchanged.
     *
     * @tparam Function The function to apply. It should take `const T&` or `T` as its last argument.
     * @tparam Params The parameters to the function, excluding the last one.
     * @param args The arguments to pass to the function. For member functions the first argument must be a class
     * instance on which to call the function.
     */
    template<auto Function, class... Params>
    void collect(Params&&... args) {
        for(auto index = m_begin; index < m_end; ++index) {
            std::invoke(Function, std::forward<Params>(args)..., m_array[index]);
        }
        m_begin = 0;
        m_end = 0;
    }

    /// Discard all elements in the queue. No destructors will be called.
    void clear() {
        m_begin = 0;
        m_end = 0;
    }

    /**
     * @brief Size of currently allocated memory.
     * Note that the occupied capacity is not equivalent to size(), but to the total amount of items inserted since the
     * last time the queue was cleared (by calling clear() or popping the last element in the queue).
     *
     * @return The maximum amount of objects of type T the underlying vector can store.
     */
    [[nodiscard]] std::size_t capacity() const {
        return m_array.capacity();
    }

    /// Amount of objects currently in the queue.
    [[nodiscard]] std::size_t size() const {
        return m_end - m_begin;
    }

    /**
     * @brief How much of the total capacity of the underlying vector is currently in use.
     * @return The total amount of objects stored in the queue since the last clear.
     */
    [[nodiscard]] std::size_t usedCapacity() const {
        return m_end;
    }

private:
    std::vector<T> m_array {};
    std::size_t m_begin {0};
    std::size_t m_end {0};
};

} // namespace Folk

#endif //SRC_UTILS__SIMPLE_QUEUE_HPP
