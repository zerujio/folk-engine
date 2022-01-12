//
// Created by sergio on 07-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__INPUT_ACTION_REGISTRY_HPP
#define INCLUDE_FOLK_INPUT__INPUT_ACTION_REGISTRY_HPP

#include "folk/input/input_code.hpp"
#include "folk/input/connection.hpp"

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

    struct InputAction {
        entt::sigh<void(InputState)> signal_handler {};
    };

    using InputMap = std::multimap<InputCode, InputAction*>;

    std::map<std::string, InputAction> m_actions {};
    InputMap m_bindings {};

public:

    /// Notify all InputActions bound to the given InputCode of an state change.
    void notify(InputCode, InputState) const;
};

} // namespace Folk

#endif //INCLUDE_FOLK_INPUT__INPUT_ACTION_REGISTRY_HPP
