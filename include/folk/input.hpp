#ifndef FOLK_INPUT__INPUT_HPP
#define FOLK_INPUT__INPUT_HPP

#include "folk/input/common.hpp"
#include "folk/input/input_code.hpp"
#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_action.hpp"
#include "folk/input/input_window_handle.hpp"
#include "folk/input/input_event_queue.hpp"

#include "folk/math/vector.hpp"

#include <functional>

namespace Folk
{

template <class C> class ScopedInitializer;

/*========== getInput ==========*/
struct Input final {
    /**
     * @brief Poll the state of a key in the current frame.
     * @return Either InputState::Press or InputState::Release.
     */
    static InputState get(Key);

    /**
     * @brief Poll the state of a MouseButton in the current frame.
     * @return Either InputState::Press or InputState::Release.
     */
    static InputState get(MouseButton);

    /**
     * @brief Poll the state of an InputCode in the current frame.
     * @return Either InputState::Press or InputState::Release.
     */
    static InputState get(InputCode);

    /**
     * @brief Poll the state of an InputAction in the current frame.
     *
     * The action is considered to have been "pressed" if any of the bound keys or mouse buttons is pressed.
     *
     * @return Either InputState::Press or InputState::Release.
     */
    static InputState get(const InputAction&);

    /// Name of a key in US ANSI layout
    static const char* getKeyName(Key);

    /// Cursor related functions
    struct Cursor final {
        Cursor() = delete;

        /// Consulta la posición del cursor.
        /**
         * \return la posición del cursor en coordenadas de la pantalla, con origen en la
         * esquina superior izquierda y medida en pixeles.
         */
        static Vec2d getPosition();

        /// Cambia la posición del cursor.
        static void setPosition(Vec2d);
    };

private:
    friend class ScopedInitializer<Input>;

    static void initialize(InputWindowHandle manager, InputEventQueue& queue);
    static void terminate();

    static InputWindowHandle s_input_manager;
    static InputEventQueue* s_input_queue_ptr;

    template<class T>
    static void inputCallback(T code, InputState state);
};

/*=============================== Mouse ======================================*/

} // namespace folk

#endif // FOLK_INPUT__INPUT_HPP