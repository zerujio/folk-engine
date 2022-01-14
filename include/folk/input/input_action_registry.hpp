//
// Created by sergio on 07-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__INPUT_ACTION_REGISTRY_HPP
#define INCLUDE_FOLK_INPUT__INPUT_ACTION_REGISTRY_HPP

#include "folk/input/input_code.hpp"
#include "folk/input/connection.hpp"
#include "folk/core/exception_handler.hpp"

#include "entt/entt.hpp"

#include <map>
#include <string>

namespace Folk {

/**
 * @brief Maintains a registry of input actions.
 *
 * An input action is a higher level abstraction to allow for input remapping and such. For example, instead of checking
 * if the space bar has been pressed, one can check the "jump" input action. An action may have more than one input code
 * assigned and they may be changed dynamically.
 */
class InputActionRegistry final {

    friend class InputActionManager;
    friend class InputActionHandle;

    struct InputAction {
        entt::sigh<std::exception_ptr(InputState)> signal_handler {};
    };

    using ActionMap = std::map<std::string, InputAction, std::less<>>;
    ActionMap m_actions {};

    using BindingMap = std::multimap<InputCode, InputAction*>;
    BindingMap m_bindings {};

public:

    /// Notify all InputActions bound to the given InputCode of an state change.
    void notify(InputCode, InputState, const ExceptionHandler&) const;
};

} // namespace Folk

#endif //INCLUDE_FOLK_INPUT__INPUT_ACTION_REGISTRY_HPP
