//
// Created by sergio on 14-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__BINDING_MAP_SINK_HPP
#define INCLUDE_FOLK_INPUT__BINDING_MAP_SINK_HPP

#include <map>

namespace Folk {

/**
 * @brief A wrapper that maintains a pointer to a std::multimap to easily bind and unbind keys to values.
 * The underlying object will be
 * @tparam K key type.
 * @tparam T value type.
 */
template<class K, class T>
class BindingMapSink {
    std::multimap<K, T*>* m_map;

public:
    explicit BindingMapSink(std::multimap<K, T*>& map) : m_map(&map) {}

    void bind(K key, T& lvalue) {
        auto[begin, end] = m_map->equal_range(key);

        // if key is already bound, return immediately
        for (auto iter = begin; iter != end; ++iter)
            if (iter->second == &lvalue)
                return;

        m_map->template emplace_hint(begin, key, &lvalue);
    }

    void unbind(K key, T& lvalue) {
        auto[begin, end] = m_map->equal_range(key);

        for (auto iter = begin; iter != end; ++iter)
            if (iter->second == &lvalue) {
                m_map->erase(iter);
                return;
            }
    }
};

} // namespace Folk

#endif //INCLUDE_FOLK_INPUT__BINDING_MAP_SINK_HPP
