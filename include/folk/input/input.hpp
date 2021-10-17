#ifndef FOLK_INPUT__INPUT_HPP
#define FOLK_INPUT__INPUT_HPP

#include <set>

namespace Folk
{

/// \brief \~spanish Teclas
/// \brief \~english Input codes for keys.
enum class Key {
    Unknown = -1,
    /* printable keys */
    Space = 32,
    Apostrophe = 39,
    Comma = 44,
    Minus = 45,
    Period = 46,
    Slash = 47,
    Num0 = 48,
    Num1 = 49,
    Num2 = 50,
    Num3 = 51,
    Num4 = 52,
    Num5 = 53,
    Num6 = 54,
    Num7 = 55,
    Num8 = 56,
    Num9 = 57,
    Semicolon = 59,
    Equal = 61,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    LeftBracket = 91,
    Backslash = 92,
    RightBracket = 93,
    GraveAccent = 96,
    world_1 = 161,
    world_2 = 162,
    
    /* function keys */
    Escape = 256,
    Enter = 257,
    Tab = 258,
    Backspace = 259,
    Insert = 260,
    Delete = 261,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    PageUp = 266,
    PageDown = 267,
    Home = 268,
    End = 269,
    CapsLock = 280,
    ScrollLock = 281,
    NumLock = 282,
    PrintScreen = 283,
    Pause = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,
    F25 = 314,
    Kp_0 = 320,
    Kp_1 = 321,
    Kp_2 = 322,
    Kp_3 = 323,
    Kp_4 = 324,
    Kp_5 = 325,
    Kp_6 = 326,
    Kp_7 = 327,
    Kp_8 = 328,
    Kp_9 = 329,
    KpDecimal = 330,
    KpDivide = 331,
    KpMultiply = 332,
    KpSubtract = 333,
    KpAdd = 334,
    KpEnter = 335,
    KpEqual = 336,
    LeftShift = 340,
    LeftControl = 341,
    LeftAlt = 342,
    LeftSuper = 343,
    RightShift = 344,
    RightControl = 345,
    RightAlt = 346,
    RightSuper = 347,
    Menu = 348
}; // enum

/// \brief \~spanish Teclas modificadoras
/// \brief \~english Flags for keyboard modifier keys.
enum class Mod {
    Shift       = 0x001,
    Control     = 0x002,
    Alt         = 0x004,
    Super       = 0x008,
    CapsLock   = 0x0010,
    NumLock    = 0x0020
};

/// \brief \~spanish Posibles estados de una tecla.
/// \brief \~english Posible key states.
enum class KeyState {
    Release = 0,
    Press = 1,
    Repeat = 2
};

/// \brief \~spanish Consultar el estado de una tecla.
/// \brief \~english Get the state of a key.
/** 
 * \~spanish
 * El estado del teclado se actualiza el inicio de cada cuadro.
 * 
 * \~english
 * The state is updated at the start of each frame. 
 * */
KeyState getKey(Key);

/// \brief \~spanish Capa de abstracción que permite la asignación de múltiples teclas a la misma acción.
/// \brief \~english An abstraction layer for input that allows for key remapping.
class InputAction {
public:
    using KeySet = std::set<Key>;
    
    /// \brief \~spanish Conjunto de teclas asignadas a esta acción.
    /// \brief \~english Keys this action keeps track of
    KeySet keys {};

    InputAction() = default;
    InputAction(KeySet &set) : keys(set) {}

    /// \brief \~spanish Consulta el estado de esta acción.
    /// \brief \~english Get the state of this action.
    /**
     * \~spanish
     * \returns KeyState::Release si no hay teclas presionadas,
     *          KeyState::Press si al menos una tecla del conjunto fue presionada
     * 
     * \~english
     * \returns keystate_release if no keys are pressed,
     *          keystate_press if at least one key is pressed,
    */
    KeyState state();
};

} // namespace folk

#endif // FOLK_INPUT__INPUT_HPP