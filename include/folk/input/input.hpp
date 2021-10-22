#ifndef FOLK_INPUT__INPUT_HPP
#define FOLK_INPUT__INPUT_HPP

#include <map>
#include <string>
#include <vector>
#include <functional>

#include <cstdint>

namespace Folk
{

/// \brief \~spanish Posibles estados de una tecla/botón.
/// \brief \~english Possible key states.
enum class InputState : uint8_t {
    Release = 0,
    Press = 1
};

#define INPUT_CODE_INT_TYPE uint16_t
using InputCodeIntType = INPUT_CODE_INT_TYPE;

/// \brief \~spanish Teclas
/// \brief \~english Input codes for keys.
/**
 * Los valores de esta enumeración fueron elegidos para transformar fácilmente
 * a los códigos que usa GLFW.
*/
enum class Key : INPUT_CODE_INT_TYPE {
    None            = 0,

    Space           = 32, // Non printable
    Apostrophe      = 39,
    Comma           = 44,
    Minus           = 45,
    Period          = 46,
    Slash           = 47,
    Num0            = 48,
    Num1            = 49,
    Num2            = 50,
    Num3            = 51,
    Num4            = 52,
    Num5            = 53,
    Num6            = 54,
    Num7            = 55,
    Num8            = 56,
    Num9            = 57,
    Semicolon       = 59,
    Equal           = 61,
    A               = 65,
    B               = 66,
    C               = 67,
    D               = 68,
    E               = 69,
    F               = 70,
    G               = 71,
    H               = 72,
    I               = 73,
    J               = 74,
    K               = 75,
    L               = 76,
    M               = 77,
    N               = 78,
    O               = 79,
    P               = 80,
    Q               = 81,
    R               = 82,
    S               = 83,
    T               = 84,
    U               = 85,
    V               = 86,
    W               = 87,
    X               = 88,
    Y               = 89,
    Z               = 90,
    LeftBracket     = 91,
    Backslash       = 92, 
    RightBracket    = 93,
    GraveAccent     = 96,
    World1          = 161,
    World2          = 162,

    // non printable
    Escape          = 256,
    Enter           = 257,
    Tab             = 258,
    Backspace       = 259,
    Insert          = 260,
    Delete          = 261,
    Right           = 262,
    Left            = 263,
    Down            = 264,
    Up              = 265,
    PageUp          = 266,
    PageDown        = 267,
    Home            = 268,
    End             = 269,
    CapsLock        = 280,
    ScrollLock      = 281,
    NumLock         = 282,
    PrintScreen     = 283,
    Pause           = 284,
    F1              = 290,
    F2              = 291,
    F3              = 292,
    F4              = 293,
    F5              = 294,
    F6              = 295,
    F7              = 296,
    F8              = 297,
    F9              = 298,
    F10             = 299,
    F11             = 300,
    F12             = 301,
    F13             = 302,
    F14             = 303,
    F15             = 304,
    F16             = 305,
    F17             = 306,
    F18             = 307,
    F19             = 308,
    F20             = 309,
    F21             = 310,
    F22             = 311,
    F23             = 312,
    F24             = 313,
    F25             = 314,
    Kp0             = 320,
    Kp1             = 321,
    Kp2             = 322,
    Kp3             = 323,
    Kp4             = 324,
    Kp5             = 325,
    Kp6             = 326,
    Kp7             = 327,
    Kp8             = 328,
    Kp9             = 329,
    KpDecimal       = 330,
    KpDivide        = 331,
    KpMultiply      = 332,
    KpSubtract      = 333,
    KpAdd           = 334,
    KpEnter         = 335,
    KpEqual         = 336,
    LeftShift       = 340,
    LeftControl     = 341,
    LeftAlt         = 342,
    LeftSuper       = 343,
    RightShift      = 344,
    RightControl    = 345,
    RightAlt        = 346,
    RightSuper      = 347,
    Menu            = 348
}; // enum class Key

/// \brief \~spanish Consultar el estado de una tecla.
/// \brief \~english Get the state of a key.
/** 
 * \~spanish
 * El estado del teclado se actualiza el inicio de cada cuadro.
 * 
 * \~english
 * The state is updated at the start of each frame. 
 * */
InputState getKey(const Key);

/// El nombre de la tecla, ajustado a la distribución de teclado.
const char* getKeyName(const Key);

using CallbackId = uint;
using KeyCallbackT = std::function<void (Key, InputState)>;

/// Añade un callback que será invocado cuando cualquier tecla cambia de estado.
/**
 * \return Un identificador que puede ser utilizado para desconectar el callback.
*/
CallbackId addKeyCallback(KeyCallbackT);

/// Quita un callback previamente registrado.
void removeKeyCallback(CallbackId);

/// \brief \~spanish Teclas modificadoras
/// \brief \~english Flags for keyboard modifier keys.
enum class ModKey {
    Shift       = 0x001,
    Control     = 0x002,
    Alt         = 0x004,
    Super       = 0x008,
    CapsLock    = 0x0010,
    NumLock     = 0x0020
};


/// Botones del mouse.
enum class MouseButton : INPUT_CODE_INT_TYPE {
    None = 0,
    Left, Right, Middle,
    Extra1, Extra2, Extra3, Extra4, Extra5
};

/// Consulta el estado de un botón del ratón.
InputState getMouseButton (const MouseButton);

using MouseButtonCallbackT = std::function<void (MouseButton, InputState)>;

/// Un callback que será invocado cuando cualquier botón del mouse cambie de estado.
/**
 * \return un identificador que debe ser utilizado para desconectar el callback.
 */
CallbackId addMouseButtonCallback(MouseButtonCallbackT);

/// Desconecta un callback previamente registrado.
void removeMouseButtonCallback(CallbackId);

/// Interfaz común para el código de una tecla o botón del mouse.
class InputCode {
public:
    /// Crea un código vacío (es decir, inválido).
    constexpr InputCode() : value(0) {}

    /// Crea un código de teclado.
    constexpr InputCode(Key key) 
        : value(static_cast<InputCodeIntType>(key)) {}

    /// Crea un código de botón del ratón.
    constexpr InputCode(MouseButton button) 
        : value(bitmask|static_cast<InputCodeIntType>(button)) {}

    /// Consulta si la enumeración subyacente es del tipo Key.
    constexpr bool isKey() const {
        return not (bitmask & value);
    }

    /// Consulta si la enumeración subyacente es del tipo MouseButton.
    constexpr bool isMouseButton() const {
        return bitmask & value;
    }

    /// Operador de conversión para el tipo Key.
    /**
     * Utilizar este operador si la enumeración almacenada no es de tipo Key es 
     * comportamiento indefinido.
    */
    constexpr operator Key() const {
        return static_cast<Key>(value);
    }
    
    /// Operador de conversión para el tipo MouseButton.
    /**
     * Utilizar este operador si la enumeración almacenada no es de tipo 
     * MouseInput es comportamiento indefinido.
     */
    constexpr operator MouseButton() const {
        return static_cast<MouseButton>(value & ~bitmask);
    }

    /// Retorna `true` si hay algún valor almacenado.
    constexpr operator bool() const {
        return static_cast<bool>(value & ~bitmask);
    }

    constexpr InputCode& operator=(Key key) {
        value = static_cast<InputCodeIntType>(key);
        return *this;
    }

    constexpr InputCode& operator=(MouseButton mb) {
        value = bitmask | static_cast<InputCodeIntType>(mb);
        return *this;
    }

    constexpr InputCode& operator=(InputCode const& other) {
        value = other.value;
        return *this;
    }

    friend constexpr bool operator==(InputCode x, InputCode y) {
        return x.value == y.value;
    }

    friend constexpr bool operator!=(InputCode x, InputCode y) {
        return x.value != y.value;
    }

    friend constexpr bool operator<(InputCode l, InputCode r) {
        return l.value < r.value;
    }

    /// El InputState de la tecla o botón.
    InputState state() const;

private:
    InputCodeIntType value;
    static const InputCodeIntType bitmask = 1 << (sizeof(InputCodeIntType) * 8 - 1);
};


using InputCodeCallbackT = std::function<void (InputCode, InputState)>;

/// Registra un callback que será invocado cuando cualquier tecla o botón cambie de estado.
/**
 * \return Un identificador que puede ser usado para desconectar el callback.
 */
CallbackId addInputCodeCallback(InputCodeCallbackT);

/// Desconecta un callback previamente registrado.
void removeInputCodeCallback(CallbackId);

/// Representa una combinación de hasta 4 teclas/botones distintos.
class InputCombination {
public:
    /// Construye una combinación vacía.
    constexpr InputCombination() = default;

    /// Construye una combinación con un único input.
    constexpr InputCombination(InputCode c) 
        : codes{c}
    {}

    constexpr InputCombination(Key k) 
        : InputCombination(InputCode(k)) 
    {}
    constexpr InputCombination(MouseButton m) 
        : InputCombination(InputCode(m)) 
    {}

    /// Construye una combinación de inputs.
    constexpr InputCombination(InputCode c0, InputCode c1) 
        : codes{c0, c1} 
    {}

    constexpr InputCombination(InputCode c0, InputCode c1, InputCode c2) 
        : codes{c0, c1, c2}
    {}

    constexpr InputCombination(InputCode c0, InputCode c1, InputCode c2, InputCode c3)
        :codes{c0, c1, c2, c3}
    {}

    /// Accede al n-ésimo elemento de la combinación (sin verificación de rango)
    constexpr InputCode& operator[](uint n) {
        return codes[n];
    }

    constexpr InputCode const& operator[](uint n) const {
        return codes[n];
    }

    friend constexpr bool operator==(InputCombination, InputCombination);
    friend constexpr bool operator!=(InputCombination, InputCombination);

    /// El estado de esta combinación de teclas/botones.
    InputState state() const;

private:
    InputCode codes[4] {};
};


/// \brief \~spanish Capa de abstracción que permite la asignación de hasta 4 teclas a la misma acción.
/// \brief \~english An abstraction layer for input that allows for key remapping.
class InputAction {

public:
    using CallbackType = std::function<void (InputState)>;

    std::string name {};

    /// Acción sin entradas asociadas.
    InputAction() = default;

    /// Acción con nombre.
    InputAction(std::string const& name_) : name(name_) {}

    using CallbackId = unsigned int;

    /// Añade un callback a la acción.
    /**
     * \param f Una función que será invocada cuando cualquiera de las teclas,
     *          botones o combinaciones asociadas a esta acción sea presionada.
     * 
     * \return Un identificador que puede ser usado para desconectar el callback.
     */
    CallbackId addCallback(CallbackType f);

    /// Quita un callback a la acción.
    /**
     * Usar un Id inválido o correspondiente a una función que ya fue desconectada
     * no tiene efecto.
     * 
     * \param id Un identificador retornado por addCallback().
    */
    void removeCallback(CallbackId id);

    /// Consulta el estado de esta accción.
    /**
     * \return KeyState::Press si al menos una de las combinaciones está activa,
     *         KeyState::Release si no.
    */
    InputState state() const;

    /// Asocia una nueva combinación de teclas a esta acción.
    /**
     * Es válido asociar teclas o botones individuales (se convierten en una 
     * combinación con un solo valor), pero no combinaciones vacías.
     * 
     * \param x una InputCombination. Puede ser un único InputCode, el cual se
     *          convertirá implícitamente a InputCombination.
     * \return El índice de la combinación en la lista de asociaciones.
    */
    uint addBinding(InputCombination x);

    /// Quita una combinación de teclas asociada.
    /**
     * Esta operación reduce en 1 los índices de las acciones posteriores a esta.
     * Por ejemplo, si una acción tiene 3 combinaciones `A`, `B` y`C` que fueron
     * asociadas en ese orden, entonces sus indices respectivos serán `0`, `1` y
     * `2`. Si se elimina la acción `B`, el índice de `C` cambiará a `1` pero el
     * de `A` se mantendrá en `0`.
     * 
     * \param el índice de la combinación a quitar.
    */
    void removeBinding(uint i);

    /// Clase
    class BindingRef;
    
    /// Cambia una combinación de teclas asociada.
    /**
     * \param k el índice de la asociación a la que acceder.
     * \param combination La nueva combinación de teclas.
     */
    void changeBinding(uint k, InputCombination combination);

private:
    /// Representa una combinación de teclas asociada a una acción.
    struct Binding {
        InputAction* action_;
        InputCombination combination_;
        InputState state_[4];

        Binding(InputAction*, InputCombination);
        Binding(Binding const&);
        Binding(Binding &&);
        ~Binding();
        
        InputState state() const;

        Binding& operator=(Binding const&);

        void changeCombination(InputCombination);

        operator InputCombination() {
            return combination_;
        }
    };

    std::vector<Binding> bindings_;
    std::map<CallbackId, CallbackType> callbacks_;

    static CallbackId next_id;

    friend class InputManager;
};

} // namespace folk

#endif // FOLK_INPUT__INPUT_HPP