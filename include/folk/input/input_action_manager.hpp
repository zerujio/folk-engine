//
// Created by sergio on 11-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__INPUT_ACTION_MANAGER_HPP
#define INCLUDE_FOLK_INPUT__INPUT_ACTION_MANAGER_HPP

#include "connection.hpp"
#include "input_action_registry.hpp"
#include "input_action_handle.hpp"

#include <string>

namespace Folk {

/**
 * @brief Manipulates an InputActionRegistry.
 */
class InputActionManager final {

    friend class InputActionHandle;
    using InputMap = InputActionRegistry::InputMap;
    using InputAction = InputActionRegistry::InputAction;

    InputActionRegistry& m_registry;

public:
    explicit InputActionManager(InputActionRegistry& registry) : m_registry(registry) {}

    /**
     * @brief Create a new input action.
     * @param name A unique name to identify the action.
     * @return A handle to the newly created action.
     * @throws RuntimeError if another action with the same name already exists.
     */
    InputActionHandle create(const char* name) const;
    InputActionHandle create(const std::string& name) const;
    InputActionHandle create(std::string&& name) const;

    /**
     * @brief Find an existing input action.
     * @param name The unique name that identifies the action.
     * @return A handle to the input action.
     * @throws RuntimeError if no action is found for the given name.
     */
    InputActionHandle get(const char* name) const;
    InputActionHandle get(const std::string& name) const;
    InputActionHandle get(std::string&& name) const;

    /**
     * @brief Removes an input action from the registry.
     * @param name The unique name that identifies the action.
     * @throws RuntimeError if no action is found with the given name.
     */
    void destroy(const char* name) const;
    void destroy(const std::string& name) const;
    void destroy(std::string&& name) const;
};

} // namespace Folk

#endif //INCLUDE_FOLK_INPUT__INPUT_ACTION_MANAGER_HPP
