//
// Created by sergio on 30-01-22.
//

#ifndef SRC_RENDER__RENDER_CONTEXT_HPP
#define SRC_RENDER__RENDER_CONTEXT_HPP

#include "folk/math/vector.hpp"

#include "folk/window/window_handle.hpp"
#include "folk/window/glfw_call.hpp"

#include "folk/window/glfw.hpp"

#include <entt/entt.hpp>

#include <map>

namespace Folk {

/**
 * @brief A handle to operate on a window's rendering context.
 * The handle remains valid as long as the window (not the WindowManager) exists.
 */ 
class RenderingWindowHandle final {

    friend class WindowManager;

public:
    /// A handle without a window associated.
    RenderingWindowHandle() = default;

    /// A handle to a window.
    RenderingWindowHandle(const WindowHandle& handle);

    /// Make the OpenGL context current for the calling thread.
    void makeContextCurrent() const;

    /// Swap the front and back buffers.
    void swapBuffers() const;

    /// (Main thread only) Set the callback to invoke whenever the frame buffer is resized.
    template<auto Func>
    void setFrameBufferSizeCallback() const {
        framebuffer_resize_callbacks[m_window_ptr].connect<Func>();
    }

    /**
     * @brief (Main thread only) Set the callback to invoke whenever the frame buffer is resized.
     * 
     * @tparam an unbound member function.
     * @param object an object on which to call the member function.
     */
    template<auto Func, class Object>
    void setFrameBufferSizeCallback(Object& object) const {
        framebuffer_resize_callbacks[m_window_ptr].connect<Func>(object);
    }

    /// (Main thread only) Get the current frame buffer size.
    [[nodiscard]] Vec2i getFrameBufferSize() const;

private:

    GLFWwindow* m_window_ptr;

    static void onWindowCreate(GLFWwindow*);
    static void onWindowDestroy(GLFWwindow*);

    static std::map<GLFWwindow*, entt::delegate<void(Vec2i)>> framebuffer_resize_callbacks;
    static void onFramebufferResize(GLFWwindow*, int, int);
};

} // namespace Folk


#endif //SRC_RENDER__RENDER_CONTEXT_HPP
