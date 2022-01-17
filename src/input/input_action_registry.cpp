//
// Created by sergio on 07-01-22.
//

#include "folk/input/input_action_registry.hpp"

namespace Folk {

void InputActionRegistry::notify(InputCode code, InputState state, const ExceptionHandler& exception_handler) const {
    auto [begin, end] = m_bindings.equal_range(code);

    auto collector = [exception_handler](const std::exception_ptr& ptr) {
        if (ptr)
            exception_handler.handleException(ptr);
    };

    for (auto iter = begin; iter != end; ++iter) {
        // "collect" exceptions and pass them to the exception handler.
        iter->second->m_signal_handler.collect(collector, state);
    }
}

} // namespace Folk