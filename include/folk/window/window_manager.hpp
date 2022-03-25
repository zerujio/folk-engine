#ifndef FOLK_WINDOW__WINDOW_MANAGER_HPP
#define FOLK_WINDOW__WINDOW_MANAGER_HPP

#include "window_handle.hpp"

namespace Folk {

/**
 * @brief Manages (i.e. takes ownership of) a window.
 *
 * NOTE: WindowingSystem must be initialized before creating non-null managers.
 */
class WindowManager final : public WindowHandle {

public:

    static constexpr Vec2i s_default_window_size {800, 600};

    /// Default constructor: creates a manager that owns a newly created window.
    explicit WindowManager(const char* window_name);
    explicit WindowManager(const std::string & window_name);

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

private:
    /// Destroy owned window, leaving this object in null state.
    void destroyWindow();
};

} // namespace Folk

#endif // FOLK_WINDOW__WINDOW_MANAGER_HPP