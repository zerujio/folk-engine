//
// Created by sergio on 11-01-22.
//

#include "folk/input/input_action_handle.hpp"

namespace Folk {

void InputActionHandle::bind(InputCode code) const {
    auto [begin, end] = m_bindings.equal_range(code);

    // check if action is already bound to this code.
    for (auto iter = begin; iter != end; ++iter)
        if (iter->second == &m_action)
            return;

    m_bindings.emplace_hint(end, code, &m_action);
}

void InputActionHandle::unbind(InputCode code) const {
    auto [begin, end] = m_bindings.equal_range(code);

    for (auto iter = begin; iter != end; ++iter)
        if (iter->second == &m_action) {
            m_bindings.erase(iter);
            return;
        }
}

bool InputActionHandle::isBound(InputCode code) const {
    auto [begin, end] = m_bindings.equal_range(code);

    for (auto iter = begin; iter != end; ++iter)
        if (iter->second == &m_action)
            return true;

    return false;
}

} // namespace Folk