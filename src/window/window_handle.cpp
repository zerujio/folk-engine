#include "folk/window/window_handle.hpp"

namespace Folk
{

WindowHandle::operator bool() const {
    return m_window_ptr;
}

bool WindowHandle::isNull() const {
    return !m_window_ptr;
}

void WindowHandle::setTitle(const char *title) const {
    GLFW::call::slow(glfwSetWindowTitle)(m_window_ptr, title);
}

void WindowHandle::setTitle(const std::string &title) const {
    setTitle(title.c_str());
}

void WindowHandle::setSize(Vec2i size) const {
    GLFW::call::slow(glfwSetWindowSize)(m_window_ptr, size.x, size.y);
}

Vec2i WindowHandle::getSize() const {
    int x, y;
    GLFW::call::slow(glfwGetWindowSize)(m_window_ptr, &x, &y);
    return {x, y};
}

void WindowHandle::clearCloseCallback() const {
    close_callbacks[m_window_ptr].reset();
}

void WindowHandle::onWindowCreate(GLFWwindow* window_ptr) {
    close_callbacks[window_ptr];
    GLFW::call::slow(glfwSetWindowCloseCallback)(window_ptr, windowCloseCallback);
}

void WindowHandle::onWindowDestroy(GLFWwindow* window_ptr) {
    close_callbacks.erase(window_ptr);
}

void WindowHandle::windowCloseCallback(GLFWwindow* window_ptr) {
    const auto& callback = close_callbacks[window_ptr];

    if (callback)
        callback();
}

std::map<GLFWwindow*, entt::delegate<void()>> WindowHandle::close_callbacks {};

} // namespace Folk
