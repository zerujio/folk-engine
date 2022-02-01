//
// Created by sergio on 30-01-22.
//

#ifndef SRC_RENDER__RENDER_CONTEXT_HPP
#define SRC_RENDER__RENDER_CONTEXT_HPP

#include "folk/math/vector.hpp"

#include "folk/window/window_manager.hpp"
#include "folk/window/glfw_call.hpp"

#include "folk/window/glfw.hpp"

namespace Folk {

/**
 * @brief A handle to operate on a window's rendering context.
 * The handle remains valid as long as the window (not the WindowManager) exists.
 */
class RenderContextHandle final {

public:
    /// A handle without a window associated.
    RenderContextHandle() = default;

    /// A handle to a window.
    RenderContextHandle(const WindowManager& manager);

    /// Make the OpenGL context current for the calling thread.
    void makeContextCurrent() const;

    /// Swap the front and back buffers.
    void swapBuffers() const;

    /// (Main thread only) Set the callback to invoke whenever the frame buffer is resized.
    template<auto Func>
    void setFrameBufferSizeCallback() const {
        FOLK_GLFW_CALL(glfwSetFramebufferSizeCallback, m_window_ptr, [](auto, int w, int h){ Func(Vec2i(w, h)); });
    }

    /// (Main thread only) Get the current frame buffer size.
    [[nodiscard]] Vec2i getFrameBufferSize() const;

protected:
    GLFWwindow* m_window_ptr;
};

} // namespace Folk


#endif //SRC_RENDER__RENDER_CONTEXT_HPP
