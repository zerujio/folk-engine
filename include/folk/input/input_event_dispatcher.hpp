//
// Created by sergio on 06-01-22.
//

#ifndef FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP
#define FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP

#include "folk/input/common.hpp"
#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_code.hpp"

#include "folk/core/exception_handler.hpp"

#include "entt/entt.hpp"

#include <queue>

namespace Folk {

    template<class InputType>
    struct InputEvent final {
        InputType code;
        InputState state;

        InputEvent(InputType code_, InputState state_) : code(code_), state(state_) {}
    };

    class InputEventDispatcher {
    public:

        friend class InputEventManager;

        /// Enqueues an event.
        /**
         * @tparam InputType type of the event (key, mouse button, input code).
         * @param input_code key or button that was pressed.
         * @param state state of the input.
         */
        template<class InputType>
        void enqueue(InputType input_code, InputState state) const {
            getQueue<InputType>().emplace(input_code, state);
        }

        /// Delivers (i.e. invokes the callbacks of) all queued events.
        void update(const ExceptionHandler& handler);

        /// Delivers all queued events of the given type.
        template<class InputType>
        void update(const ExceptionHandler& handler){

            auto& sigh = getSigH<InputType>();
            auto& queue = getQueue<InputType>();

            auto collector = [handler](const std::exception_ptr& ptr) noexcept {
                handler.handleException(ptr);
            };

            while(!queue.empty()) {
                const auto& event = queue.front();
                sigh.collect(collector, event.code, event.state);
                queue.pop();
            }
        }

    private:

        // Event queues
        template<class InputType>
        using EventQueue = std::queue<InputEvent<InputType>>;

        EventQueue<Key> m_key_queue {};
        EventQueue<MouseButton> m_mb_queue {};
        EventQueue<InputCode> m_code_queue {};

        template<class InputType> constexpr EventQueue<InputType>& getQueue();
        template<class InputType> constexpr const EventQueue<InputType>& getQueue() const;

        template<> [[nodiscard]] constexpr EventQueue<Key>& getQueue() { return m_key_queue; }
        template<> [[nodiscard]] constexpr const EventQueue<Key>& getQueue() const { return m_key_queue; }

        template<> [[nodiscard]] constexpr EventQueue<MouseButton>& getQueue() { return m_mb_queue; }
        template<> [[nodiscard]] constexpr const EventQueue<MouseButton>& getQueue() const { return m_mb_queue; }

        template<> [[nodiscard]] constexpr EventQueue<InputCode>& getQueue() { return m_code_queue; }
        template<> [[nodiscard]] constexpr const EventQueue<InputCode>& getQueue() const { return m_code_queue; }

        // Signal handlers
        template<class InputType>
        using SignalHandler = entt::sigh<std::exception_ptr(InputType, InputState)>;

        SignalHandler<Key> m_key_sigh {};
        SignalHandler<MouseButton> m_mb_sigh {};
        SignalHandler<InputCode> m_code_sigh {};

        template<class InputType> constexpr SignalHandler<InputType>& getSigH();
        template<class InputType> constexpr const SignalHandler<InputType>& getSigH() const;

        template<> [[nodiscard]] constexpr SignalHandler<Key>& getSigH() { return m_key_sigh; }
        template<> [[nodiscard]] constexpr const SignalHandler<Key>& getSigH() const { return m_key_sigh; }

        template<> [[nodiscard]] constexpr SignalHandler<MouseButton>& getSigH() { return m_mb_sigh; }
        template<> [[nodiscard]] constexpr const SignalHandler<MouseButton>& getSigH() const { return m_mb_sigh; }

        template<> [[nodiscard]] constexpr SignalHandler<InputCode>& getSigH() { return m_code_sigh; }
        template<> [[nodiscard]] constexpr const SignalHandler<InputCode>& getSigH() const { return m_code_sigh; }
    };

}

#endif //FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP
