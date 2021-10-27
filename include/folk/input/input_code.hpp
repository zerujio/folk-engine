#ifndef FOLK_INPUT__INPUT_CODE_HPP
#define FOLK_INPUT__INPUT_CODE_HPP

#include "enums.hpp"

namespace Folk
{

/// Interfaz común para el código de una tecla o botón del mouse.
class InputCode {

public:
    /// Crea un código con el valor por defecto Key::Space.
    constexpr InputCode() : value(0) {}

    /// Crea un código de teclado.
    constexpr InputCode(Key key)
        : value(static_cast<InputCodeIntType>(key)) {}

    /// Crea un código de botón del ratón.
    constexpr InputCode(MouseButton button)
        : value(static_cast<InputCodeIntType>(button)) {}

    /// Consulta si la enumeración subyacente es del tipo Key.
    constexpr bool isKey() const {
        return value > static_cast<InputCodeIntType>(MouseButton::Extra5);
    }

    /// Consulta si la enumeración subyacente es del tipo MouseButton.
    constexpr bool isMouseButton() const {
        return value <= static_cast<InputCodeIntType>(MouseButton::Extra5);
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
        return static_cast<MouseButton>(value);
    }

    constexpr InputCode& operator=(Key key) {
        value = static_cast<InputCodeIntType>(key);
        return *this;
    }

    constexpr InputCode& operator=(MouseButton mb) {
        value = static_cast<InputCodeIntType>(mb);
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

};

} // namespace Folk

#endif // FOLK_INPUT__INPUT_CODE_HPP