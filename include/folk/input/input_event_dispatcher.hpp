//
// Created by sergio on 06-01-22.
//

#ifndef FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP
#define FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP

#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_code.hpp"

#include "entt/entt.hpp"

namespace Folk {

    template<class CodeType>
    class InputEvent {
        CodeType code;
        InputState state;
    };

    class InputEventDispatcher {

        entt::dispatcher m_dispatcher {};

    public:

        class ConnectionManager;
        friend class InputEventDispatcher::ConnectionManager;

        using Connection = entt::connection;
        using ScopedConnection = entt::scoped_connection;

        /// Enqueues an event.
        /**
         *
         * @tparam CodeType type of the event (key, mouse button, input code).
         * @param input_code key or button that was pressed.
         * @param state state of the input.
         */
        template<class CodeType>
        void enqueue(CodeType input_code, InputState state) {
            m_dispatcher.template enqueue<InputEvent<CodeType>>(input_code, state);
        }

        /// Immediately triggers an event.
        template<class CodeType>
        void trigger(CodeType input_code, InputState state) {
            m_dispatcher.template trigger<InputEvent<CodeType>>(input_code, state);
        }

        /// Triggers all queued events.
        void update() const;

        /// Triggers all queued events of the given type.
        template<class CodeType>
        void update() const {
            m_dispatcher.update<InputEvent<CodeType>>();
        }
    };

    class InputEventDispatcher::ConnectionManager {

        template<class InputType>
        using Sink = decltype(entt::dispatcher().sink<InputEvent<InputType>>());

        Sink<Key> m_key_sink;
        Sink<MouseButton> m_mb_sink;
        Sink<InputCode> m_code_sink;

        template<class InputType>
        Sink<InputType>& getSink();

        template<>
        Sink<Key>& getSink<Key>() { return m_key_sink; }

        template<>
        Sink<MouseButton>& getSink<MouseButton>() { return m_mb_sink; }

        template<>
        Sink<InputCode>& getSink<InputCode>() { return m_code_sink; }

    public:
        explicit ConnectionManager(InputEventDispatcher& dispatcher) :
            m_key_sink(dispatcher.m_dispatcher.sink<InputEvent<Key>>()),
            m_mb_sink(dispatcher.m_dispatcher.sink<InputEvent<MouseButton>>()),
            m_code_sink(dispatcher.m_dispatcher.sink<InputEvent<InputCode>>())
        {}

        using Connection = entt::connection;
        using ScopecConnection = entt::scoped_connection;

        /**
         * @brief Establish a callback to be invoked whenever a key is pressed.
         *
         * The signature for a callback must be equivalent to `void (InputType, InputState)`. The first argument is the
         * enum value for the key or mouse button. The second is the state of the input.
         *
         * @tparam InputType The type of input to set this callback for. May be Key, MouseButton or InputCode
         * (for both keyboard and mouse button input).
         * @tparam Function The function or method
         * @tparam Payload Type of the payload arguments
         * @param payload A set of values to be passed to the callback on each invocation.
         * @return A Connection object that may be used to disconnect the callback directly or through a ScopedReference.
         */
        template<class InputType, auto Function, class... Payload>
        Connection connect(Payload&&... payload) {
            return getSink<InputType>().template connect<Function>(std::forward<Payload>(payload)...);
        }

        /// Disconnect a free function.
        template<class InputType, auto Function>
        void disconnect() {
            getSink<InputType>().template disconnect<Function>();
        }

        /// Disconnect an instance's member function.
        template<class InputType, auto Function, class Object>
        void disconnect(const Object& instance) {
            getSink<InputType>().template disconnect<Function>(instance);
        }

        /// Disconnect all functions bound to a specific instance.
        template<class InputType, class Object>
        void disconnect(const Object& instance) {
            getSink<InputType>().disconnect(instance);
        }
    };

}

#endif //FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP
