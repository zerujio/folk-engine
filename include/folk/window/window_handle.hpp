#ifndef FOLK_WINDOW__WINDOW_HANDLE_HPP
#define FOLK_WINDOW__WINDOW_HANDLE_HPP

#include "folk/math/vector.hpp"

#include "glfw.hpp"
#include "glfw_call.hpp"

#include <entt/entt.hpp>

#include <string>
#include <map>

namespace Folk {

/**
 * @brief References an OS window.
 */
class WindowHandle {

    friend class WindowingSystem;
    friend class InputWindowHandle;
    friend class RenderingWindowHandle;

public:

    /// A default constructed WindowHandle references no window (i.e. is a null handle).
    WindowHandle() = default;

    /// Evaluates to true if the handle is not null.
    operator bool() const;

    /// Returns true if the handle does not reference a window.
    [[nodiscard]] bool isNull() const;

    /// Set window title, as shown in the OS.
    void setTitle(const char* title) const;
    void setTitle(const std::string& title) const;

    /// Set width and height of application window
    void setSize(Vec2i size) const;

    /// Retrieve width and height of application window
    [[nodiscard]] Vec2i getSize() const;

    /// Sets a callback for when the window is set to close,
    template<auto FreeFunction>
    void setCloseCallback() const {
        close_callbacks[m_window_ptr].connect<FreeFunction>();
    }

    template<auto MemberFunction, class Object>
    void setCloseCallback(Object & object) const {
        close_callbacks[m_window_ptr].connect<MemberFunction>(object);
    }

    /// Clears the close callback.
    void clearCloseCallback() const;


protected:

    GLFWwindow* m_window_ptr {nullptr};

    WindowHandle(GLFWwindow* ptr) : m_window_ptr(ptr) {}

    static void onWindowCreate(GLFWwindow* window_ptr);
    static void onWindowDestroy(GLFWwindow* window_ptr);

private:

    static void windowCloseCallback(GLFWwindow* window_ptr);
    static std::map<GLFWwindow*, entt::delegate<void()>> close_callbacks;
};

} // namespace folk

#endif//FOLK_WINDOW__WINDOW_HANDLE_HPP