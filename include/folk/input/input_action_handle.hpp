//
// Created by sergio on 11-01-22.
//

#ifndef SRC_INPUT__INPUT_ACTION_HANDLE_HPP
#define SRC_INPUT__INPUT_ACTION_HANDLE_HPP

#include "input_action_manager.hpp"

#include <functional>


namespace Folk {

/// A handle to an InputAction.
class InputActionHandle final {

    using InputAction = InputActionManager::InputAction;
    using InputMap = InputActionManager::InputMap;

    InputAction& m_action;
    InputMap& m_bindings;

    explicit InputActionHandle(InputAction& action, InputMap& map ) : m_action(action), m_bindings(map) {}

public:
    /**
     * @brief Bind this input action to an input code.
     * If the action was already bound to the given code this operation has no effect.
     *
     * @param handle a handle obtained through the get function.
     * @param code a Key or MouseButton code.
     */
    void bind(InputCode code) const;

    /**
     * @brief Unbind an input code.
     * If the action was not bound to the given code this operation has no effect.
     *
     * @param code a Key or MouseButton value.
     */
    void unbind(InputCode code) const;

    /**
     * @brief Check if this action is bound to an input code.
     * @param code The code for the key or mouse button
     * @return whether the input is bound to the action.
     */
    [[nodiscard]] bool isBound(InputCode code) const;

    /**
     * @brief Connect a function to an InputAction as a callback
     * If the candidate function was already connected, this function has no effect.
     *
     * @tparam Function The function to connect.
     * @tparam Payload The type of the payload arguments.
     * @param payload arguments that will be passed to the callback on each invocation. If Function is a member
     * function, then the first element of the payload must be an instance on which to call it.
     * @return a Connection object which allows the callback to be disconnected, manually or through an
     * ScopedConnection object, without the need to keep a reference to this InputAction.
     */
    template<auto Function, class... Payload>
    Connection connect(Payload&&... payload) const;

    /**
     * @brief Disconnect a free function callback.
     * If the free function had not been previously connected, this operation will have no effect.
     *
     * @tparam Function a free function.
     */
    template<auto Function>
    void disconnect() const;

    /**
     * @brief Disconnect an instance's member function.
     * If the member function had not been previously connected, this operation will have no effect.
     *
     * @tparam Function The member function to disconnect.
     * @tparam Object The type of the instance.
     * @param instance The instance to which the connected member function was bound.
     */
    template<auto Function, class Object>
    void disconnect(const Object& instance) const;

    /**
     * @brief Disconnect all member functions bound to an instance.
     * If no member functions bound to the instance were previously connected, then this operation will have no effect.
     * @tparam Object
     * @param instance
     */
    template<class Object>
    void disconnect(const Object& instance) const;
};


// Template definitions

template<auto Function, class... Payload>
Connection InputActionHandle::connect(Payload &&... payload) const {
    m_action.signal_handler.sink().connect<Function>(std::forward<Payload>(payload)...);
}

template<auto Function>
void InputActionHandle::disconnect() const {
    m_action.signal_handler.disconnect<Function>();
}

template<auto Function, class Object>
void InputActionHandle::disconnect(const Object &instance) const {
    m_action.signal_handler.disconnect<Function>(instance);
}

template<class Object>
void InputActionHandle::disconnect(const Object &instance) const {
    m_action.signal_handler.disconnect(instance);
}

} // namespace Folk

#endif //SRC_INPUT__INPUT_ACTION_HANDLE_HPP
