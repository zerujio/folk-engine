//
// Created by sergio on 11-01-22.
//

#ifndef SRC_INPUT__INPUT_ACTION_HANDLE_HPP
#define SRC_INPUT__INPUT_ACTION_HANDLE_HPP

#include "folk/input/input_code.hpp"
#include "folk/input/binding_map_sink.hpp"
#include "folk/input/connection.hpp"
#include "folk/core/exception_handler.hpp"
#include "folk/utils/no_except_function_wrapper.hpp"
#include "folk/utils/simple_set.hpp"

#include "entt/entt.hpp"

#include <exception>
#include <functional>

namespace Folk {

/// A handle to an InputAction.
class InputAction final {

    friend class InputActionRegistry;

    SimpleSet<InputCode> m_binding_set {};
    entt::sigh<std::exception_ptr(InputState)> m_signal_handler {};
    BindingMapSink<InputCode, InputAction> m_binding_sink;

public:
    /**
     * @brief Construct an input action.
     * @param map A binding map that will be notified whenever a key is bound or unbound to this action.
     */
    explicit InputAction(BindingMapSink<InputCode, InputAction> map) : m_binding_sink(map) {}

    InputAction(const InputAction&) = delete;
    InputAction(InputAction&&) = delete;
    ~InputAction();

    /**
     * @brief Bind this input action to an input code.
     * If the action was already bound to the given code this operation has no effect.
     *
     * @param handle a handle obtained through the get function.
     * @param code a Key or MouseButton code.
     */
    void bind(InputCode code);

    /**
     * @brief Unbind an input code.
     * If the action was not bound to the given code this operation has no effect.
     *
     * @param code a Key or MouseButton value.
     */
    void unbind(InputCode code);

    /// Return the set of bound input codes.
    [[nodiscard]] const SimpleSet<InputCode>& bindings() const;

    /**
     * @brief Check if this action is bound to an input code.
     * @param code The code for the key or mouse button
     * @return whether the input is bound to the action.
     */
    [[nodiscard]] bool isBound(InputCode code) const;

    /**
     * @brief Connect a free function as a callback.
     * @tparam Function The callback function.
     * @return A Connection object which may be used to disconnect the callback (or create a ScopedConnection).
     */
    template<auto Function>
    Connection connect() {
        return entt::sink(m_signal_handler).template connect<NoExceptFunctionWrapper<Function, InputState>>();
    }

    /**
     * @brief Connect a bound member to the InputAction as a callback.
     * If the candidate function was already connected, this operation has no effect.
     *
     * @tparam Function The member function to connect.
     * @tparam Object The type of the instance on which to call the function.
     * @param instance The instance on which to call the function.
     * @return A Connection object which may be used to disconnect the callback (or create a ScopedConnection).
     */
    template<auto Function, class Object>
    Connection connect(Object& instance) {
        return entt::sink(m_signal_handler).template connect<NoExceptFunctionWrapper<Function, Object&, InputState>>(instance);
    }

    /**
     * @brief Disconnect a free function.
     * @tparam Function the function to disconnect.
     */
    template<auto Function>
    void disconnect() {
        entt::sink(m_signal_handler).template disconnect<NoExceptFunctionWrapper<Function, InputState>>();
    }

    /**
     * @brief Disconnect a bound member function.
     * @tparam Function the function to disconnect.
     * @tparam Object the type of the instance.
     * @param instance the instance to which the member function was bound.
     */
    template<auto Function, class Object>
    void disconnect(Object& instance) {
        entt::sink(m_signal_handler).template disconnect<NoExceptFunctionWrapper<Function, Object&, InputState>>(instance);
    }

    /**
     * @brief Disconnect all member functions bound to an instance.
     * @tparam Object The type of the instance.
     * @param instance An instance of type Object.
     */
    template<class Object>
    void disconnect(Object& instance) {
        entt::sink(m_signal_handler).disconnect(instance);
    }
};

} // namespace Folk

#endif //SRC_INPUT__INPUT_ACTION_HANDLE_HPP