#include "folk/window/window_manager.hpp"
#include "../render/rendering_window_handle.hpp"

namespace Folk {

WindowManager::WindowManager(const char* window_name)
{
    m_window_ptr = GLFW::call::slow(glfwCreateWindow)(s_default_window_size.x, s_default_window_size.y, window_name, nullptr, nullptr);

    WindowHandle::onWindowCreate(m_window_ptr);
    RenderingWindowHandle::onWindowCreate(m_window_ptr);
}

WindowManager::WindowManager(const std::string &window_name) : WindowManager(window_name.c_str()) {}

WindowManager::WindowManager(WindowManager &&other) noexcept : WindowHandle(other.m_window_ptr) {
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

    WindowHandle::onWindowDestroy(m_window_ptr);
    RenderingWindowHandle::onWindowDestroy(m_window_ptr);

    m_window_ptr = nullptr;
}

} // namespace folk