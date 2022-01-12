//
// Created by sergio on 06-01-22.
//

#ifndef INCLUDE_FOLK_UTILS__SIMPLE_SET_HPP
#define INCLUDE_FOLK_UTILS__SIMPLE_SET_HPP

#include <vector>
#include <functional>
#include <algorithm>

namespace Folk {

    /// A simple implementation of a set.
    /**
     * A simple set based on a std::vector. Used when the only relevant operations are insertion, deletion, iteration
     * and contain queries.
     * @tparam T Type of the elements. Must be comparable and support copy construction. Ideally just a numeric type.
     */
    template<class T>
    class SimpleSet {
        std::vector<T> m_vector {};

    public:

        /// Check if the set is empty.
        [[nodiscard]] bool empty() const {
            return m_vector.empty();
        }

        /// Insert a new element into the set.
        /**
         * @param value element to add to the set.
         * @return whether the operation inserted a new element.
         */
        bool insert(const T& value) {
            auto it = std::lower_bound(m_vector.begin(), m_vector.end(), value);

            if (it == m_vector.end() or *(it + 1) == value)
                return false;

            m_vector.insert(it, value);
            return true;
        }

        /// Remove an element from the set.
        /**
         * @param value element to remove from the set.
         * @return whether the element was removed (true if the element was present, false if not).
         */
        bool remove(const T& value) {
            auto it = std::lower_bound(m_vector.begin(), m_vector.end(), value);

            if (it == m_vector.end() or *(++it) != value)
                return false;

            m_vector.erase(it);
            return true;
        }

        /// Check if an element is preset in the set.
        bool contains(const T& value) const {
            return std::binary_search(m_vector.cbegin(), m_vector.cend(), value);
        }

        /// Read-only access to underlying vector.
        const std::vector<T>& data() const {
            return m_vector;
        }

        /// Remove all elements.
        void clear() {
            m_vector.clear();
        }
    };

} // namespace Folk

#endif //INCLUDE_FOLK_UTILS__SIMPLE_SET_HPP
