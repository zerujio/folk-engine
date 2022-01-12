#ifndef FOLK_INPUT__INPUT_HPP
#define FOLK_INPUT__INPUT_HPP

#include "folk/input/common.hpp"
#include "folk/input/input_code.hpp"
#include "folk/input/input_action.hpp"
#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"

#include "folk/math/vector.hpp"

#include <functional>

namespace Folk
{

/*========== getInput ==========*/

/**
 * @brief Poll the state of a key in the current frame.
 * @return Either InputState::Press or InputState::Release.
 */
InputState getInput(Key);

/**
 * @brief Poll the state of a MouseButton in the current frame.
 * @return Either InputState::Press or InputState::Release.
 */
InputState getInput(MouseButton);

/**
 * @brief Poll the state of an InputCode in the current frame.
 * @return Either InputState::Press or InputState::Release.
 */
InputState getInput(InputCode);

/**
 * @brief Poll the state of an InputAction in the current frame.
 *
 * The action is considered to have been "pressed" if any of the bound keys or mouse buttons is pressed.
 *
 * @return Either InputState::Press or InputState::Release.
 */
InputState getInput(const InputAction&);

/*============================ MouseButton ===================================*/

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


/*=============================== Mouse ======================================*/

namespace Cursor {

enum class CallbackId : IdIntType {};
using CallbackType = std::function<void (Vec2f)>;

/// Consulta la posición del cursor.
/**
 * \return la posición del cursor en coordenas de la pantalla, con origen en la 
 * esquina superior izquierda y medida en pixeles.
 */
Vec2d getPosition();

/// Cambia la posición del cursor.
void setPosition(Vec2d);

/// Añade un callback que será invocado cada vez que la posición del ratón cambie.
/**
 * \return un identificador que puede ser utilizado para quitar este callback.
*/
CallbackId addCallback(CallbackType&&);

/// Quita un callback previamente asociado.
void removeCallback(CallbackId const);

enum class Mode {Normal, Hidden, Disabled};

/// Cambia el modo del cursor.
/**
 * - Normal: funcionamiento estándar.
 * - Hidden: igual al modo normal, pero el cursor no es visible.
 * - Disabled: movimiento ilimitado, cursor invisible y re-centrado 
 *  automáticamente. Sirve para implementar _mouse look_.
*/
void setMode(Mode);

/// Consulta el modo del cursor.
Mode getMode();

/// Consulta si la plataforma soporta el modo _raw motion_ (sin escalamiento ni aceleración).
bool isRawMotionSupported();

void setRawMotionEnabled(bool);

bool getRawMotionEnabled();

} // namespace Mouse

namespace Scroll {

enum class CallbackId : IdIntType {};
using CallbackType = std::function<void(Vec2d)>;

/// Añade un callback que será invocado cada vez que se haga _scroll_.
/**
 * El scroll se provee a la función como un vector de dos dimensiones que 
 * representa el desplazamiento en cada eje. La mayoría de los ratones comunes
 * sólo tienen desplazamiento vertical (eje Y).
*/
CallbackId addCallback(CallbackType&&);

/// Quita un callback anteriormente configurado.
void removeCallback(CallbackId const);

} // namespace Scroll

} // namespace folk

#endif // FOLK_INPUT__INPUT_HPP