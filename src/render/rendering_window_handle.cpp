#include "rendering_window_handle.hpp"

namespace Folk {

RenderingWindowHandle::RenderingWindowHandle(const WindowHandle& handle) : m_window_ptr(handle.m_window_ptr) {}

void RenderingWindowHandle::makeContextCurrent() const {
    GLFW::call::slow(glfwMakeContextCurrent)(m_window_ptr);
    if (!gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ))
        throw CriticalError("GLAD: GL function loading failed.");
}

void RenderingWindowHandle::swapBuffers() const {
    GLFW::call::fast(glfwSwapBuffers)(m_window_ptr);
}   

Vec2i RenderingWindowHandle::getFrameBufferSize() const {
    int w, h;
    GLFW::call::fast(glfwGetFramebufferSize)(m_window_ptr, &w, &h);
    return {w, h};
}


void RenderingWindowHandle::onWindowCreate(GLFWwindow* window_ptr) {
    framebuffer_resize_callbacks[window_ptr];
    GLFW::call::slow(glfwSetFramebufferSizeCallback)(window_ptr, onFramebufferResize);
}

void RenderingWindowHandle::onWindowDestroy(GLFWwindow* window_ptr) {
    GLFW::call::slow(glfwSetFramebufferSizeCallback)(window_ptr, nullptr);
    framebuffer_resize_callbacks.erase(window_ptr);
}

void RenderingWindowHandle::onFramebufferResize(GLFWwindow* window_ptr, int width, int height) {
    const auto& callback = framebuffer_resize_callbacks[window_ptr];

    if (callback)
        callback({width, height});
}

std::map<GLFWwindow*, entt::delegate<void(Vec2i)>> RenderingWindowHandle::framebuffer_resize_callbacks {};

} // namespace Folk