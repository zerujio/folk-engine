//
// Created by sergio on 11-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__INPUT_ACTION_MANAGER_HPP
#define INCLUDE_FOLK_INPUT__INPUT_ACTION_MANAGER_HPP

#include "connection.hpp"
#include "input_action_registry.hpp"
#include "input_action.hpp"

#include <string>

namespace Folk {

/**
 * @brief Manipulates an InputActionRegistry.
 */
class InputActionManager final {

    friend class InputAction;

    using ActionMap = InputActionRegistry::ActionMap;

    InputActionRegistry* m_registry;

    template<class T>
    InputAction& create(T name) const;

    template<class T>
    InputAction& get(T name) const;

    template<class T>
    void destroy(T name) const;

public:
    explicit InputActionManager(InputActionRegistry& registry) : m_registry(&registry) {}

    /**
     * @brief Create a new input action.
     * @param name A unique name to identify the action.
     * @return A handle to the newly created action.
     * @throws RuntimeError if another action with the same name already exists.
     */
    InputAction & create(const char* name) const;
    InputAction & create(const std::string& name) const;

    /**
     * @brief Find an existing input action.
     * @param name The unique name that identifies the action.
     * @return A handle to the input action.
     * @throws RuntimeError if no action is found for the given name.
     */
    InputAction & get(const char* name) const;
    InputAction & get(const std::string& name) const;

    /**
     * @brief Removes an input action from the registry.
     * @param name The unique name that identifies the action.
     * @throws RuntimeError if no action is found with the given name.
     */
    void destroy(const char* name) const;
    void destroy(const std::string& name) const;
};

} // namespace Folk

#endif //INCLUDE_FOLK_INPUT__INPUT_ACTION_MANAGER_HPP
