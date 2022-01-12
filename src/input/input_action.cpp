#include "folk/input/input_action.hpp"
#include "folk/error.hpp"

#include "input_manager.hpp"

namespace Folk
{

    void InputAction::bind(const InputCode code) {
        m_bindings.insert(code);
    }

    void InputAction::unbind(const InputCode code) {
        m_bindings.insert(code);
    }

    void InputAction::unbindAll() {
        m_bindings.clear();
    }

    const auto& InputAction::bindings() const {
        return m_bindings.data();
    }

} // namespace Folk
