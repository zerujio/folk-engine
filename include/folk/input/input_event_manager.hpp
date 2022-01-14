//
// Created by sergio on 13-01-22.
//

#ifndef SRC_INPUT_INPUT_EVENT_DISPATCHER_CPP__INPUT_EVENT_MANAGER_HPP
#define SRC_INPUT_INPUT_EVENT_DISPATCHER_CPP__INPUT_EVENT_MANAGER_HPP

#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_code.hpp"
#include "folk/input/input_event_dispatcher.hpp"
#include "folk/input/connection.hpp"

#include "folk/utils/no_except_function_wrapper.hpp"

namespace Folk {

class InputEventManager final {

    template<class InputType>
    using Sink = decltype(entt::dispatcher().sink<InputEvent<InputType>>());

    Sink<Key> m_key_sink;
    Sink<MouseButton> m_mb_sink;
    Sink<InputCode> m_code_sink;

    template<class InputType>
    Sink<InputType> &getSink();

    template<>
    Sink<Key> &getSink<Key>() { return m_key_sink; }

    template<>
    Sink<MouseButton> &getSink<MouseButton>() { return m_mb_sink; }

    template<>
    Sink<InputCode> &getSink<InputCode>() { return m_code_sink; }

public:
    explicit InputEventManager(InputEventDispatcher &dispatcher) :
            m_key_sink(dispatcher.m_dispatcher.sink<InputEvent<Key>>()),
            m_mb_sink(dispatcher.m_dispatcher.sink<InputEvent<MouseButton>>()),
            m_code_sink(dispatcher.m_dispatcher.sink<InputEvent<InputCode>>()) {}

    /**
     * @brief Set a free function as an input callback.
     * @tparam InputType The type of the input (Key, MouseButton, or InputCode).
     * @tparam Function The function to connect. Should be equivalent to `void (InputType, InputState)`.
     * @return A Connection object.
     */
    template<auto Function, class InputType>
    Connection connect() const {
        return getSink<InputType>().template connect<NoExceptFunctionWrapper<Function>>();
    }

    /**
     * @brief Set a bound member function as an input callback.
     * The user must ensure that the lifetime of the bound instance exceeds that of the callback.
     * @tparam InputType Type of input to be notified of (Key, MouseButton, or InputCode).
     * @tparam Function The member function to connect.
     * @tparam Object The type of the instance. Should be equivalent to `void (InputType, InputState)`.
     * @param instance An Object instance on which to call the member function.
     * @return A Connection object.
     */
    template<auto Function, class InputType, class Object>
    Connection connect(Object& instance) const {
        return getSink<InputType>().template connect<NoExceptFunctionWrapper<Function, void>>(instance);
    }

    /// Disconnect a free function.
    template<auto Function, class InputType>
    void disconnect() const {
        getSink<InputType>().template disconnect<NoExceptFunctionWrapper<Function, void>>();
    }

    /// Disconnect an instance's member function.
    template<auto Function, class InputType, class Object>
    void disconnect(const Object &instance) const {
        getSink<InputType>().template disconnect<NoExceptFunctionWrapper<Function, void>>(instance);
    }

    /// Disconnect all functions bound to a specific instance.
    template<class InputType, class Object>
    void disconnect(const Object &instance) const {
        getSink<InputType>().disconnect(instance);
    }
};

} // namespace Folk

#endif //SRC_INPUT_INPUT_EVENT_DISPATCHER_CPP__INPUT_EVENT_MANAGER_HPP
