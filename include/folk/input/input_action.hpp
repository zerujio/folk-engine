#ifndef FOLK_INPUT__INPUT_ACTION_HPP
#define FOLK_INPUT__INPUT_ACTION_HPP

#include "folk/input/common.hpp"
#include "folk/input/input_code.hpp"

#include "folk/utils/simple_set.hpp"

#include "entt/entt.hpp"

namespace Folk
{

/// \brief \~spanish Capa de abstracción que permite la asignación de hasta 4 teclas a la misma acción.
/// \brief \~english An abstraction layer for input that allows for key remapping.
class InputAction final {

    /// The InputManager can trigger the callbacks.
    friend class InputManager;

    entt::sigh<void(InputState)> m_sigh {};
    entt::sink<void(InputState)> m_sink {m_sigh};
    SimpleSet<InputCode> m_bindings {};

public:
    using Connection = entt::connection;
    using ScopedConnection = entt::scoped_connection;

    /// Connects a callback function.
    /**
     *
     * @tparam Function The function to connect. It should be equivalent to void(*)(InputCode).
     * @tparam Payload The types of the payload arguments.
     * @param payload A set of arguments that will be passed to the listener on each invocation. Pass an in instance as
     * first argument for member functions.
     * @return A Connection object. May be used to disconnect the function manually or through a ScopedConnection object.
     */
    template<auto Function, class... Payload>
    Connection connect(Payload... payload) {
        return m_sink.connect<Function>(std::forward<Payload>(payload)...);
    }

    /// Disconnect a function.
    /**
     * If the Function was not previously connected this call will have no effect.
     *
     * @tparam Function the function to disconnect.
     */
    template<auto Function>
    void disconnect() {
        m_sink.disconnect<Function>();
    }

    /// Disconnect an instance's member function.
    /**
     * If the member function was not previously connected then this call will have no effect.
     * @tparam MemberFunction the function to disconnect.
     * @tparam Object The class to which the function belongs.
     * @param instance The instance to which the function is bound.
     */
    template<auto MemberFunction, class Object>
    void disconnect(const Object& instance) {
        m_sink.disconnect<MemberFunction>(instance);
    }

    /// Disconnect all callbacks bound to a specific instance.
    /**
     * If there are no connections to the given instance then this call will have no effect.
     * @tparam Object The type of the object to disconnect.
     * @param instance An instance to disconnect all callbacks to bound to any of its members.
     */
    template<class Object>
    void disconnect(const Object& instance) {
        m_sink.disconnect(instance);
    }

    /// Disconnect all callbacks bound to this Action.
    void disconnectAll() {
        m_sink.disconnect();
    }

    /// Binds a new input to this action.
    /**
     * If the input was already bound this call will have no effect.
     * @param code a Key or MouseButton.
     */
    void bind(InputCode code);

    /**
     * @brief Unbind an input code.
     * If the input code had not been previously bound, this call will have no effect.
     * @param code a Key or MouseButton.
     */
    void unbind(InputCode code);

    /// Removes all bindings.
    void unbindAll();

    /// Read-only access to bound input codes.
    [[nodiscard]]
    const auto& bindings() const;
};

} // namespace Folk

#endif // FOLK_INPUT__INPUT_ACTION_HPP