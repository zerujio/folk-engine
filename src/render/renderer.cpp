#include "renderer.hpp"

#include "folk/render/visual_component.hpp"
#include "folk/scene/transform_component.hpp"

#include "../core/engine_singleton.hpp"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace Folk {

Renderer::Renderer(ExceptionHandler& exc, const WindowManager& win)
: window_mngr(win)
{

}

Renderer::~Renderer() {

}

void Renderer::drawFrame(SceneManager& scene_mngr, std::chrono::duration<double> delta)
{
    auto wsize = window_mngr.getSize();

    Matrix4f view_mtx;
    Matrix4f proj_mtx;
    
    auto cam_entity = scene_mngr.camera();

    // calculate view and projection matrix
    if (cam_entity == entt::null) {
        // at_vector = {0, 0, 0};
        // eye_vector = {0, 0, 0};
    
    } else {
        // eye_vector = {0, 0, 0} * camera_transform_matrix
        // at_vector = {0, 0, 1} * camera_transform_matrix
    }

    auto reg_view = scene_mngr.registry().view<SceneGraphNode, const VisualComponent>();
    reg_view.each(
            [this, wsize, view_mtx, proj_mtx]
            (const auto entity, SceneGraphNode& transform, const VisualComponent& visual)
            {
                // setViewTransform(view_mtx, proj_mtx);

                auto mesh = visual.visual->getMesh();
                // setVertexBuffer( mesh->vertex_buffer );
                // setIndexBuffer( mesh->index_buffer );

                // setTransform( transform.transformMatrix() );

                // setProgram(visual.visual->getMaterial()->getShader()->handle):
                // draw();
            }
    );

    // end frame (swap buffers?)
}

void Renderer::drawPerfMon(const PerformanceMonitor& perf_monitor,
                           DeltaClock::milliseconds_double delta) noexcept
{
    // draw perfomance monitor
}

} // namespace folk