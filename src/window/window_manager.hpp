#ifndef FOLK_WINDOW__MODULE_HPP
#define FOLK_WINDOW__MODULE_HPP

#include "folk/math/vector.hpp"

#include "../utils/singleton.hpp"

#include "GLFW/glfw3.h"

#include "entt/entt.hpp"

#include <string>

namespace Folk {

/**
 * @brief Manages (i.e. takes ownership of) a window.
 *
 * NOTE: WindowingSystem must be initialized before creating non-null managers.
 */
class WindowManager final {

    friend class WindowingSystem;
    friend class InputManager;

public:

    /// Default constructor: creates a manager that owns a newly created window.
    explicit WindowManager(const char* window_name);
    explicit WindowManager(const std::string & window_name);

    /**
     * @brief Takes ownership of an existing window.
     * @param window_ptr a pointer to a GLFW window struct. Pass nullptr to create a manager that owns no window.
     *
     * WARNING: operations other that move assignment and bool casting on a null manager are undefined behavior.
     */
    explicit WindowManager(GLFWwindow* window_ptr);

    /// Deleted copy constructor.
    WindowManager(const WindowManager &) = delete;

    /**
     * @brief takes ownership of another object's window.
     * @param other a manager to take the window from. Will be left owning no window.
     */
    WindowManager(WindowManager && other) noexcept ;

    /// Deleted copy assignment operator.
    WindowManager & operator=(const WindowManager &) = delete;

    /// Takes ownership of another object's window, similarly to move construction.
    WindowManager & operator=(WindowManager && other) noexcept;

    /// Destroys the owned window, if any.
    ~WindowManager();

    /// Evaluates to true if the manager owns a window.
    operator bool() const;

    /// Returns true if the manager does not own a window.
    [[nodiscard]] bool isNull() const;

    /// Set window title, as shown in the OS.
    void setTitle(const char* title) const;
    void setTitle(const std::string& title) const;

    /// Set width and height of application window
    void setSize(Vector2<int> size) const;

    /// Retrieve width and height of application window
    [[nodiscard]] Vector2<int> getSize() const;

private:
    static constexpr Vector2<int> s_default_window_size {800, 600};

    GLFWwindow* m_window_ptr;

    /// Destroy owned window, leaving this object in null state.
    void destroyWindow();
};

#define WINDOW WindowManager::instance()

} // namespace folk

#endif//FOLK_WINDOW__MODULE_HPP