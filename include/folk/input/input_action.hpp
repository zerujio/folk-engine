#ifndef FOLK_INPUT__INPUT_ACTION_HPP
#define FOLK_INPUT__INPUT_ACTION_HPP

#include "input.hpp"
#include "enums.hpp"

#include <string>
#include <functional>
#include <map>
#include <set>

namespace Folk
{

/// \brief \~spanish Capa de abstracción que permite la asignación de hasta 4 teclas a la misma acción.
/// \brief \~english An abstraction layer for input that allows for key remapping.
class InputAction {

public:
    /// Crea una nueva InputAction.
    /**
     * \return una referencia a la acción creada.
    */
    static InputAction& create(std::string const& name);

    /// Busca una acción con el nombre dado.
    static InputAction& get(std::string const& name);

    /// Destruye una acción con el nombre dado.
    static void destroy(std::string const& name);

    enum class CallbackId : IdIntType {};
    using CallbackType = std::function<void (InputState)>;

    /// Añade un callback a la acción.
    /**
     * \param f Una función que será invocada cuando cualquiera de las teclas,
     *          botones o combinaciones asociadas a esta acción sea presionada.
     * 
     * \return Un identificador que puede ser usado para desconectar el callback.
     */
    CallbackId addCallback(CallbackType &&f);

    /// Quita un callback a la acción.
    /**
     * Usar un Id inválido o correspondiente a una función que ya fue desconectada
     * no tiene efecto.
     * 
     * \param id Un identificador retornado por addCallback().
    */
    void removeCallback(CallbackId const id);

    /// Consulta el estado de esta accción.
    /**
     * \return KeyState::Press si al menos una de las asociaciones está activa,
     *         KeyState::Release si no.
    */
    InputState state() const;

    /// Asocia una nueva tecla o botón a esta InputAction.
    /**
     * Si el input ya estaba asociado, esta acción no tiene efecto.
     * 
     * \param x Un InputCode.
     * \return El índice del InputCode en la lista de asociaciones.
    */
    void addBinding(InputCode const x);

    /// Quita una tecla/botón asociada.
    /**
     * Si el input no había sido asociado antes, esta acción no tiene efecto.
    */
    void removeBinding(InputCode const code);

    /// Quita todas las asociaciones.
    void clearBindings();
    
    /// Cantidad de _bindings_ (combinaciones de inputs) asociadas a esta acción.
    uint bindingCount() {return bindings_.size();}

    std::set<InputCode> const& bindings() const {
        return bindings_;
    }

private:
    InputAction() = default;
    InputAction(InputAction const&) = delete;
    InputAction(InputAction &&);
    InputAction& operator=(InputAction const&) = delete;

    std::map<IdIntType, CallbackType> callbacks_;
    std::set<InputCode> bindings_;

    static IdIntType next_id_;

    friend class InputManager;
    friend class InputActionProxy;

    void bind(InputCode const);
    void unbind(InputCode const);
};

} // namespace Folk

#endif // FOLK_INPUT__INPUT_ACTION_HPP