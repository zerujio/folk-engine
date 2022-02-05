//
// Created by sergio on 11-01-22.
//

#include "folk/input/input_action_manager.hpp"
#include "folk/error.hpp"

namespace Folk {

template<class StringType>
InputAction& InputActionManager::create(StringType name) const {
    auto [iter, inserted] = m_registry->m_actions.template emplace(name, m_registry->m_binding_map);

    if (!inserted)
        throw Error("An InputAction by this name already exists.");

    return iter->second;
}

InputAction & InputActionManager::create(const char *name) const {
    return create<decltype(name)>(name);
}

InputAction & InputActionManager::create(const std::string& name) const {
    return create<decltype(name)>(name);
}


template<class StringType>
InputAction& InputActionManager::get(StringType name) const {
    auto iter = m_registry->m_actions.find<StringType>(name);

    if (iter == m_registry->m_actions.end())
        throw Error("No InputAction by this name exists.");

    return iter->second;
}

InputAction & InputActionManager::get(const char *name) const {
    return get<decltype(name)>(name);
}

InputAction & InputActionManager::get(const std::string &name) const {
    return get<decltype(name)>(name);
}


template<class StringType>
void InputActionManager::destroy(StringType name) const {
    auto action_iter = m_registry->m_actions.find<StringType>(name);

    // check if action exists
    if (action_iter == m_registry->m_actions.end())
        throw Error("No InputAction by this name exists.");

    // destroy the action
    m_registry->m_actions.erase(action_iter);
}

void InputActionManager::destroy(const char *name) const {
    destroy<decltype(name)>(name);
}

void InputActionManager::destroy(const std::string &name) const {
    destroy<decltype(name)>(name);
}

} // namespace Folk