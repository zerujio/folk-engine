//
// Created by sergio on 13-01-22.
//

#ifndef SRC_INPUT_INPUT_EVENT_DISPATCHER_CPP__INPUT_EVENT_MANAGER_HPP
#define SRC_INPUT_INPUT_EVENT_DISPATCHER_CPP__INPUT_EVENT_MANAGER_HPP

#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_code.hpp"
#include "folk/input/input_callback_registry.hpp"
#include "folk/input/connection.hpp"

#include "folk/utils/no_except_function_wrapper.hpp"

namespace Folk {

class InputCallbackManager final {

public:
    explicit InputCallbackManager(InputCallbackRegistry &registry)
    : m_key_sink(registry.m_key_sigh), m_mb_sink(registry.m_mb_sigh), m_code_sink(registry.m_code_sigh) {}

    /**
     * @brief Set a free function as an input callback.
     * @tparam InputType The type of the input (Key, MouseButton, or InputCode).
     * @tparam Function The function to connect. Should be equivalent to `void (InputType, InputState)`.
     * @return A Connection object.
     */
    template<auto Function, class InputType>
    Connection connect() {
        return getSink<InputType>().template connect<NoExceptFunctionWrapper<Function, InputType, InputState>>();
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
    Connection connect(Object& instance) {
        return getSink<InputType>().template connect<NoExceptFunctionWrapper<Function, Object&, InputType, InputState>>(instance);
    }

    /// Disconnect a free function.
    template<auto Function, class InputType>
    void disconnect() {
        getSink<InputType>().template disconnect<NoExceptFunctionWrapper<Function, InputType, InputState>>();
    }

    /// Disconnect an instance's member function.
    template<auto Function, class InputType, class Object>
    void disconnect(const Object &instance) {
        getSink<InputType>().template disconnect<NoExceptFunctionWrapper<Function, Object&, InputType, InputState>>(instance);
    }

    /// Disconnect all functions bound to a specific instance.
    template<class InputType, class Object>
    void disconnect(const Object &instance) {
        getSink<InputType>().disconnect(instance);
    }

private:
    template<class InputType>
    using Sink = entt::sink<std::exception_ptr(InputType, InputState)>;

    Sink<Key> m_key_sink;
    Sink<MouseButton> m_mb_sink;
    Sink<InputCode> m_code_sink;

    template<class InputType>
    Sink<InputType> &getSink();
};

} // namespace Folk

#endif //SRC_INPUT_INPUT_EVENT_DISPATCHER_CPP__INPUT_EVENT_MANAGER_HPP
