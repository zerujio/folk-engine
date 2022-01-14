//
// Created by sergio on 11-01-22.
//

#include "folk/input/input_action_manager.hpp"
#include "folk/error.hpp"

namespace Folk {

template<class StringType>
InputActionHandle InputActionManager::create(StringType name) const {
    auto iter = m_registry.m_actions.find<StringType>(name);

    if (iter != m_registry.m_actions.end())
        throw FOLK_RUNTIME_ERROR("An InputAction by this name already exists.");

    return {m_registry.m_actions[name], m_registry.m_bindings};
}

InputActionHandle InputActionManager::create(const char *name) const {
    return create<decltype(name)>(name);
}

InputActionHandle InputActionManager::create(const std::string& name) const {
    return create<decltype(name)>(name);
}


template<class StringType>
InputActionHandle InputActionManager::get(StringType name) const {
    auto iter = m_registry.m_actions.find<StringType>(name);

    if (iter == m_registry.m_actions.end())
        throw FOLK_RUNTIME_ERROR("No InputAction by this name exists.");

    return {iter->second, m_registry.m_bindings};
}

InputActionHandle InputActionManager::get(const char *name) const {
    return get<decltype(name)>(name);
}

InputActionHandle InputActionManager::get(const std::string &name) const {
    return get<decltype(name)>(name);
}


template<class StringType>
void InputActionManager::destroy(StringType name) const {
    auto action_iter = m_registry.m_actions.find<StringType>(name);

    // check if action exists
    if (action_iter == m_registry.m_actions.end())
        throw FOLK_RUNTIME_ERROR("No InputAction by this name exists.");

    // find and erase all bindings of this action
    for (auto bind_iter = m_registry.m_bindings.begin(); bind_iter != m_registry.m_bindings.end(); ) {
        if (bind_iter->second == &(action_iter->second))
            bind_iter = m_registry.m_bindings.erase(bind_iter);
        else
            ++bind_iter;
    }

    // destroy the action
    m_registry.m_actions.erase(action_iter);
}

void InputActionManager::destroy(const char *name) const {
    destroy<decltype(name)>(name);
}

void InputActionManager::destroy(const std::string &name) const {
    destroy<decltype(name)>(name);
}

} // namespace Folk