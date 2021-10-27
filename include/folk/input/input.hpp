#ifndef FOLK_INPUT__INPUT_HPP
#define FOLK_INPUT__INPUT_HPP

#include "common.hpp"
#include "enums.hpp"
#include "input_code.hpp"
#include "input_action.hpp"

#include <functional>

namespace Folk
{

/*============================== Key =========================================*/

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

enum class Key_CallbackId : IdIntType {};
using Key_CallbackType = std::function<void (Key, InputState)>;

/// Añade un callback que será invocado cuando cualquier tecla cambia de estado.
/**
 * \return Un identificador que puede ser utilizado para desconectar el callback.
*/
Key_CallbackId addKeyCallback(Key_CallbackType&&);

/// Quita un callback previamente registrado.
void removeKeyCallback(Key_CallbackId const);


/*============================ MouseButton ===================================*/

/// Consulta el estado de un botón del ratón.
InputState getMouseButton (const MouseButton);

enum class  MouseButton_CallbackId : IdIntType {};
using MouseButton_CallbackType = std::function<void (MouseButton, InputState)>;

/// Un callback que será invocado cuando cualquier botón del mouse cambie de estado.
/**
 * \return un identificador que debe ser utilizado para desconectar el callback.
 */
MouseButton_CallbackId addMouseButtonCallback(MouseButton_CallbackType&&);

/// Desconecta un callback previamente registrado.
void removeMouseButtonCallback(MouseButton_CallbackId const);


/*=========================== InputCode ======================================*/

enum class InputCode_CallbackId : IdIntType {};
using InputCode_CallbackType = std::function<void (InputCode, InputState)>;

/// Registra un callback que será invocado cuando cualquier tecla o botón cambie de estado.
/**
 * \return Un identificador que puede ser usado para desconectar el callback.
 */
InputCode_CallbackId addInputCodeCallback(InputCode_CallbackType&&);

/// Desconecta un callback previamente registrado.
void removeInputCodeCallback(InputCode_CallbackId const);


} // namespace folk

#endif // FOLK_INPUT__INPUT_HPP