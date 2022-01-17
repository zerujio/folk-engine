#ifndef FOLK_INPUT__INPUT_HPP
#define FOLK_INPUT__INPUT_HPP

#include "folk/input/common.hpp"
#include "folk/input/input_code.hpp"
#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_action.hpp"

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

/*=============================== Mouse ======================================*/

namespace Cursor {

/// Consulta la posición del cursor.
/**
 * \return la posición del cursor en coordenadas de la pantalla, con origen en la
 * esquina superior izquierda y medida en pixeles.
 */
Vec2d getPosition();

/// Cambia la posición del cursor.
void setPosition(Vec2d);

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

} // namespace folk

#endif // FOLK_INPUT__INPUT_HPP