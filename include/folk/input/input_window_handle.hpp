//
// Created by sergio on 24-01-22.
//

#ifndef SRC_INPUT__INPUT_HANDLER_HPP
#define SRC_INPUT__INPUT_HANDLER_HPP

#include "folk/input/input_code.hpp"
#include "folk/window/window_handle.hpp"
#include "folk/window/glfw_call.hpp"
#include "cast.hpp"

#include <GLFW/glfw3.h>

namespace Folk {

/**
 * @brief A lightweight object that wraps the windowing system's input polling functions for a window.
 */
class InputWindowHandle final {
public:
    /**
     * @brief Create an input manager for a window.
     * The input manager will remain valid as long as the window (not the window manager) exists. This means that the
     * window manager from which the object was created can be safely moved from.
     * @param manager A window manager.
     */
    explicit InputWindowHandle(const WindowHandle& window);

    /**
     * @brief Create an input manager not bound to a window.
     * Operations other than assignment on a default-initialized input handler will result in an exception.
     */
    InputWindowHandle() = default;

    /// Poll the state of a key.
    [[nodiscard]] InputState getKey(Key key) const;

    /// Poll the state of a mouse button.
    [[nodiscard]] InputState getMouseButton(MouseButton mouse_button) const;

    /// Get the current position of the mouse cursor.
    [[nodiscard]] Vec2d getCursorPosition() const;

    /// Set a new position for the mouse cursor.
    void setCursorPosition(Vec2d position) const;

    /// Evaluates to true if there's a window associated.
    operator bool() const;

    /// Sets the manager to default initialized state (no window associated).
    void clear();

    /// Configures a key callback.
    template<void (*Function)(Key, InputState)>
    void setKeyCallback() const {

        GLFW::call::slow(glfwSetKeyCallback)(m_window_ptr, [](GLFWwindow*, int key, int, int state, int){
            Function(keyCast(key), stateCast(state));
        });
    }

    /// Removes currently bound key callback.
    void clearKeyCallback() const;

    /// Configures a mouse button callback.
    template<void (*Function)(MouseButton, InputState)>
    void setMouseButtonCallback() const {
        GLFW::call::slow(glfwSetMouseButtonCallback)(m_window_ptr, [](GLFWwindow*, int button, int state, int){
            Function(mouseButtonCast(button), stateCast(state));
        });
    }

    /// Removes currently bound mouse callback.
    void clearMouseButtonCallback() const;

private:
    GLFWwindow* m_window_ptr {nullptr};
};

} // namespace Folk


#endif //SRC_INPUT__INPUT_HANDLER_HPP
