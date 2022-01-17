//
// Created by sergio on 14-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__INPUT_REGISTRY_HPP
#define INCLUDE_FOLK_INPUT__INPUT_REGISTRY_HPP

#include "input_callback_registry.hpp"
#include "input_callback_manager.hpp"
#include "input_action_registry.hpp"
#include "input_action_manager.hpp"
#include "common.hpp"

#include "folk/core/exception_handler.hpp"

namespace Folk {

class InputRegistry final {

    friend class InputRegistryManager;
    friend class Scene;

    InputCallbackRegistry m_event_registry {};
    InputActionRegistry m_action_registry {};

public:
    /// Invoke input callbacks for the scene.
    template<class InputType>
    void notify(InputType code, InputState state, const ExceptionHandler& handler) const noexcept {
        m_event_registry.template notify(code, state, handler);
        m_action_registry.notify(code, state, handler);
    }
};

class InputRegistryManager final {
public:
    InputCallbackManager events;
    InputActionManager actions;

    explicit InputRegistryManager(InputRegistry& registry);
};

} // namespace Folk

#endif //INCLUDE_FOLK_INPUT__INPUT_REGISTRY_HPP
