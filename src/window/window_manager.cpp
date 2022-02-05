#include "folk/window/window_manager.hpp"

#include "folk/core/game.hpp"

namespace Folk {

WindowManager::WindowManager(const char* window_name)
{
    m_window_ptr = GLFW::call::slow(glfwCreateWindow)(s_default_window_size.x, s_default_window_size.y, window_name,
                                                      nullptr, nullptr);
}

WindowManager::WindowManager(const std::string &window_name) : WindowManager(window_name.c_str()) {}

WindowManager::WindowManager(WindowManager &&other) noexcept : m_window_ptr(other.m_window_ptr) {
    other.m_window_ptr = nullptr;
}

WindowManager &WindowManager::operator=(WindowManager &&other) noexcept {
    if (m_window_ptr)
        destroyWindow();

    m_window_ptr = other.m_window_ptr;
    other.m_window_ptr = nullptr;

    return *this;
}

WindowManager::~WindowManager() {
    if (m_window_ptr)
        destroyWindow();
}

void WindowManager::destroyWindow() {
    GLFW::call::slowNoExcept(glfwDestroyWindow)(m_window_ptr);
    m_window_ptr = nullptr;
}

WindowManager::operator bool() const {
    return m_window_ptr;
}

bool WindowManager::isNull() const {
    return !m_window_ptr;
}

void WindowManager::setTitle(const char *title) const {
    GLFW::call::slow(glfwSetWindowTitle)(m_window_ptr, title);
}

void WindowManager::setTitle(const std::string &title) const {
    setTitle(title.c_str());
}

void WindowManager::setSize(Vec2i size) const {
    GLFW::call::slow(glfwSetWindowSize)(m_window_ptr, size.x, size.y);
}

Vec2i WindowManager::getSize() const {
    int x, y;
    GLFW::call::slow(glfwGetWindowSize)(m_window_ptr, &x, &y);
    return {x, y};
}

GLFWwindow *WindowManager::handle() const {
    return m_window_ptr;
}

void WindowManager::clearCloseCallback() const {
    GLFW::call::slow(glfwSetWindowCloseCallback)(m_window_ptr, nullptr);
}

} // namespace folk