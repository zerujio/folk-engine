#ifndef FOLK_INPUT__INPUT_CODE_HPP
#define FOLK_INPUT__INPUT_CODE_HPP

#include "common.hpp"
#include "key.hpp"
#include "mouse_button.hpp"

namespace Folk
{

/// Interfaz común para el código de una tecla o botón del mouse.
class InputCode {

public:
    /// Crea un código con el valor por defecto Key::Space.
    constexpr InputCode() noexcept : value(0) {}

    /// Crea un código de teclado.
    constexpr InputCode(Key key) noexcept : value(static_cast<InputCodeIntType>(key)) {}

    /// Crea un código de botón del ratón.
    constexpr InputCode(MouseButton button) noexcept : value(static_cast<InputCodeIntType>(button)) {}

    /// Consulta si la enumeración subyacente es del tipo Key.
    [[nodiscard]] constexpr bool isKey() const noexcept {
        return value > static_cast<InputCodeIntType>(MouseButton::Extra5);
    }

    /// Consulta si la enumeración subyacente es del tipo MouseButton.
    [[nodiscard]] constexpr bool isMouseButton() const noexcept {
        return value <= static_cast<InputCodeIntType>(MouseButton::Extra5);
    }

    /// Operador de conversión para el tipo Key.
    /**
     * Utilizar este operador si la enumeración almacenada no es de tipo Key es 
     * comportamiento indefinido.
    */
    constexpr explicit operator Key() const noexcept {
        return static_cast<Key>(value);
    }
    
    /// Operador de conversión para el tipo MouseButton.
    /**
     * Utilizar este operador si la enumeración almacenada no es de tipo 
     * MouseInput es comportamiento indefinido.
     */
    constexpr explicit operator MouseButton() const noexcept {
        return static_cast<MouseButton>(value);
    }

    constexpr InputCode& operator=(Key key) noexcept {
        value = static_cast<InputCodeIntType>(key);
        return *this;
    }

    constexpr InputCode& operator=(MouseButton mb) noexcept {
        value = static_cast<InputCodeIntType>(mb);
        return *this;
    }

    constexpr InputCode& operator=(InputCode const& other) noexcept {
        value = other.value;
        return *this;
    }

    friend constexpr bool operator==(InputCode x, InputCode y) noexcept {
        return x.value == y.value;
    }

    friend constexpr bool operator!=(InputCode x, InputCode y) noexcept {
        return x.value != y.value;
    }

    friend constexpr bool operator<(InputCode l, InputCode r) noexcept {
        return l.value < r.value;
    }

private:
    InputCodeIntType value;

};

} // namespace Folk

#endif // FOLK_INPUT__INPUT_CODE_HPP