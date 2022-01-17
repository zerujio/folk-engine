//
// Created by sergio on 11-01-22.
//

#include "folk/input/input_action.hpp"

namespace Folk {

InputAction::~InputAction() {
    for (auto code : m_binding_set.data())
        m_binding_sink.unbind(code, *this);
}

void InputAction::bind(InputCode code) {
    // check if action is already bound to this code.
    if (m_binding_set.contains(code))
        return;

    m_binding_set.insert(code);
    m_binding_sink.bind(code, *this);
}

void InputAction::unbind(InputCode code) {
    // check if action is bound to this code.
    if (!m_binding_set.contains(code))
        return;

    // add code to set
    m_binding_set.remove(code);
    // find and erase references to this action in input map
    m_binding_sink.unbind(code, *this);
}

bool InputAction::isBound(InputCode code) const {
    return m_binding_set.contains(code);
}

const SimpleSet<InputCode> &InputAction::bindings() const {
    return m_binding_set;
}

} // namespace Folk