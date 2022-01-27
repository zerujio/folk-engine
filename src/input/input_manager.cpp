//
// Created by sergio on 24-01-22.
//

#include "input_manager.hpp"

namespace Folk {

InputManager::InputManager(const WindowManager &manager) : m_window_ptr(manager.m_window_ptr) {}

InputState InputManager::getKey(Key key) const {
    return stateCast(FOLK_GLFW_CALL(glfwGetKey, m_window_ptr, intCast(key)));
}

InputState InputManager::getMouseButton(MouseButton mouse_button) const {
    return stateCast(FOLK_GLFW_CALL(glfwGetMouseButton, m_window_ptr, intCast(mouse_button)));
}

Vec2d InputManager::getCursorPosition() const {
    double x, y;
    FOLK_GLFW_CALL(glfwGetCursorPos, m_window_ptr, &x, &y);
    return {x, y};
}

void InputManager::setCursorPosition(Vec2d position) const {
    FOLK_GLFW_CALL(glfwSetCursorPos, m_window_ptr, position.x, position.y);
}

InputManager::operator bool() const {
    return m_window_ptr;
}

void InputManager::clear() {
    m_window_ptr = nullptr;
}

void InputManager::clearKeyCallback() const {
    FOLK_GLFW_CALL(glfwSetMouseButtonCallback, m_window_ptr, nullptr);
}

void InputManager::clearMouseButtonCallback() const {
    FOLK_GLFW_CALL(glfwSetMouseButtonCallback, m_window_ptr, nullptr);
}

} // namespace Folk