//
// Created by sergio on 24-01-22.
//

#ifndef SRC_INPUT__INPUT_HANDLER_HPP
#define SRC_INPUT__INPUT_HANDLER_HPP

#include "../window/window_manager.hpp"

#include "folk/input/input_code.hpp"

namespace Folk {

/**
 * @brief A lightweight object that wraps the windowing system's input polling functions for a window.
 */
class InputManager final {
public:
    /**
     * @brief Create an input manager for a window.
     * The input manager will remain valid as long as the window (not the window manager) exists. This means that the
     * window manager from which the object was created can be safely moved from.
     * @param manager A window manager.
     */
    explicit InputManager(const WindowManager& manager);

    /**
     * @brief Create an input manager not bound to a window.
     * Operations other than assignment on a default-initialized input handler will result in an exception.
     */
    InputManager() = default;

    /// Poll the state of a key.
    [[nodiscard]] InputState getKey(Key key) const;

    /// Poll the state of a mouse button.
    [[nodiscard]] InputState getMouseButton(MouseButton mouse_button) const;

    /// Get the current position of the mouse cursor.
    [[nodiscard]] Vec2d getCursorPosition() const;

    /// Set a new position for the mouse cursor.
    void setCursorPosition(Vec2d position) const;

private:
    GLFWwindow* m_window_ptr {nullptr};
};

} // namespace Folk


#endif //SRC_INPUT__INPUT_HANDLER_HPP
