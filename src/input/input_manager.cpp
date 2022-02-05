//
// Created by sergio on 24-01-22.
//

#include "folk/input/input_manager.hpp"

namespace Folk {

InputManager::InputManager(const WindowManager &manager) : m_window_ptr(manager.m_window_ptr) {}

InputState InputManager::getKey(Key key) const {
    return stateCast(GLFW::call::fast(glfwGetKey)(m_window_ptr, intCast(key)));
}

InputState InputManager::getMouseButton(MouseButton mouse_button) const {
    return stateCast(GLFW::call::fast(glfwGetMouseButton)(m_window_ptr, intCast(mouse_button)));
}

Vec2d InputManager::getCursorPosition() const {
    double x, y;
    GLFW::call::fast(glfwGetCursorPos)(m_window_ptr, &x, &y);
    return {x, y};
}

void InputManager::setCursorPosition(Vec2d position) const {
    GLFW::call::fast(glfwSetCursorPos)(m_window_ptr, position.x, position.y);
}

InputManager::operator bool() const {
    return m_window_ptr;
}

void InputManager::clear() {
    m_window_ptr = nullptr;
}

void InputManager::clearKeyCallback() const {
    GLFW::call::fast(glfwSetMouseButtonCallback)(m_window_ptr, nullptr);
}

void InputManager::clearMouseButtonCallback() const {
    GLFW::call::fast(glfwSetMouseButtonCallback)(m_window_ptr, nullptr);
}

} // namespace Folk