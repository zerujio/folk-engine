#include "folk/input/input_window_handle.hpp"

namespace Folk {

InputWindowHandle::InputWindowHandle(const WindowHandle &window) : m_window_ptr(window.m_window_ptr) {}

InputState InputWindowHandle::getKey(Key key) const {
    return stateCast(GLFW::call::fast(glfwGetKey)(m_window_ptr, intCast(key)));
}

InputState InputWindowHandle::getMouseButton(MouseButton mouse_button) const {
    return stateCast(GLFW::call::fast(glfwGetMouseButton)(m_window_ptr, intCast(mouse_button)));
}

Vec2d InputWindowHandle::getCursorPosition() const {
    double x, y;
    GLFW::call::fast(glfwGetCursorPos)(m_window_ptr, &x, &y);
    return {x, y};
}

void InputWindowHandle::setCursorPosition(Vec2d position) const {
    GLFW::call::fast(glfwSetCursorPos)(m_window_ptr, position.x, position.y);
}

InputWindowHandle::operator bool() const {
    return m_window_ptr;
}

void InputWindowHandle::clear() {
    m_window_ptr = nullptr;
}

void InputWindowHandle::clearKeyCallback() const {
    GLFW::call::fast(glfwSetMouseButtonCallback)(m_window_ptr, nullptr);
}

void InputWindowHandle::clearMouseButtonCallback() const {
    GLFW::call::fast(glfwSetMouseButtonCallback)(m_window_ptr, nullptr);
}

} // namespace Folk