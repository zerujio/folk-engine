//
// Created by sergio on 06-01-22.
//

#ifndef FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP
#define FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP

#include "folk/input/common.hpp"
#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_code.hpp"

#include "folk/utils/exception_handler.hpp"

#include "entt/entt.hpp"

#include <queue>

namespace Folk {

    class InputCallbackRegistry {
    public:

        friend class InputCallbackManager;

        /// Invokes callbacks.
        template<class InputType>
        void notify(InputType code, InputState state, const ExceptionHandler& handler) const {
            auto collector = [handler](const std::exception_ptr& ptr) noexcept {
                if (ptr)
                    handler.handleException(ptr);
            };

            getSigH<InputType>().collect(collector, code, state);
        }

    private:
        // Signal handlers
        template<class InputType>
        using SignalHandler = entt::sigh<std::exception_ptr(InputType, InputState)>;

        SignalHandler<Key> m_key_sigh {};
        SignalHandler<MouseButton> m_mb_sigh {};
        SignalHandler<InputCode> m_code_sigh {};

        template<class InputType> constexpr SignalHandler<InputType>& getSigH();
        template<class InputType> constexpr const SignalHandler<InputType>& getSigH() const;
    };

template<> [[nodiscard]] constexpr InputCallbackRegistry::SignalHandler<Key>& InputCallbackRegistry::getSigH() { return m_key_sigh; }
template<> [[nodiscard]] constexpr const InputCallbackRegistry::SignalHandler<Key>& InputCallbackRegistry::getSigH() const { return m_key_sigh; }

template<> [[nodiscard]] constexpr InputCallbackRegistry::SignalHandler<MouseButton>& InputCallbackRegistry::getSigH() { return m_mb_sigh; }
template<> [[nodiscard]] constexpr const InputCallbackRegistry::SignalHandler<MouseButton>& InputCallbackRegistry::getSigH() const { return m_mb_sigh; }

template<> [[nodiscard]] constexpr InputCallbackRegistry::SignalHandler<InputCode>& InputCallbackRegistry::getSigH() { return m_code_sigh; }
template<> [[nodiscard]] constexpr const InputCallbackRegistry::SignalHandler<InputCode>& InputCallbackRegistry::getSigH() const { return m_code_sigh; }

} // namespace Folk

#endif //FOLK_INPUT__INPUT_EVENT_DISPATCHER_HPP
