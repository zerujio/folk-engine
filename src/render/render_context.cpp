//
// Created by sergio on 30-01-22.
//

#include "render_context.hpp"

namespace Folk {

RenderContextHandle::RenderContextHandle(const WindowManager &manager) : m_window_ptr(manager.m_window_ptr) {}

void RenderContextHandle::makeContextCurrent() const {
    FOLK_GLFW_CALL(glfwMakeContextCurrent, m_window_ptr);
    if (!gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ))
        throw FOLK_CRITICAL_ERROR("GLAD: GL function loading failed.");
}

void RenderContextHandle::swapBuffers() const {
    FOLK_GLFW_CALL(glfwSwapBuffers, m_window_ptr);
}

Vec2i RenderContextHandle::getFrameBufferSize() const {
    int w, h;
    FOLK_GLFW_CALL(glfwGetFramebufferSize, m_window_ptr, &w, &h);
    return {w, h};
}

} // namespace Folk