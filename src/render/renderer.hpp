#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "folk/math/vector.hpp"

#include "../utils/delta_clock.hpp"
#include "../utils/performance_monitor.hpp"
#include "../utils/scoped_initializer.hpp"

#include "../scene/scene_manager.hpp"

#include "folk/render/shader.hpp"
#include "folk/render/material.hpp"
#include "folk/render/texture.hpp"
#include "folk/render/visual.hpp"
#include "folk/render/visual_component.hpp"

#include "rendering_window_handle.hpp"

#include <vector>


namespace Folk {

/**
 * @brief Handles rendering operations.
 */
struct Renderer final {
    
    /**
     * @brief Construct a new Renderer object.
     * 
     * @param handle A handle to the window to render to.
     */
    Renderer(RenderingWindowHandle handle);

    /**
     * @brief Enqueue a draw call.
     * 
     * @param transform_matrix A transformation matrix for the object (the 'u_model' shader uniform).
     * @param visual A Visual object.
     */
    void draw(const Mat4& transform_matrix, const VisualComponent& visual);

    /**
     * @brief Process queued draw calls.
     * 
     * @param camera_transform Transform matrix that determines the position and orientation of the camera.
     * @param camera Camera component.
     */
    void finishFrame(const Mat4& camera_transform, const CameraComponent& camera);

    /// Draw the performance monitor.
    void drawPerfMon(const PerformanceMonitor&, DeltaClock::milliseconds_double) noexcept;

    /// Set the clear screen color.
    void setClearColor(Vec4 color) const;

private:
    
    RenderingWindowHandle m_window_handle;

    bool m_frame_buffer_size_changed {true};
    Vec2i m_frame_buffer_size {};

    struct DrawCall {
        Mat4 transform;
        std::shared_ptr<Visual> visual;
    };

    std::vector<DrawCall> draw_call_queue {};

    void setFrameBufferSize(Vec2i size);

    static void setUserUniforms(const Material& material);

    static void setTransformUniforms(const Mat4& model, const Mat4& view, const Mat4& projection, const Material& material);

    static void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                                GLsizei length, const GLchar* message, const void* userParam);
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP