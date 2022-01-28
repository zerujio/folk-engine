#include "renderer.hpp"

#include "folk/render/visual_component.hpp"
#include "folk/scene/transform_component.hpp"

#include "../core/engine_singleton.hpp"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace Folk {

Renderer::Renderer(ExceptionHandler& exc, const WindowManager& win)
    : bgfx_callback_handler(exc), window_mngr(win)
{
    // bgfx
    bgfx::renderFrame();

    bgfx::Init bgfx_init;
    bgfx_init.platformData.ndt = glfwGetX11Display();
    bgfx_init.platformData.nwh = (void*)(uintptr_t) glfwGetX11Window(window_mngr.handle());

    auto window_size = window_mngr.getSize();
    bgfx_init.resolution.width = window_size.x;
    bgfx_init.resolution.height = window_size.y;
    bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx_init.callback = &bgfx_callback_handler;

    // bgfx_init.type = bgfx::RendererType::OpenGL;

    if (!bgfx::init(bgfx_init))
        throw FOLK_CRITICAL_ERROR("bgfx initialization failed");

    // view_id = 0;bgfx_callback_handler
	bgfx::setViewClear(view_id, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
	bgfx::setViewRect(view_id, 0, 0, window_size.x, window_size.y);

    const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
    const bx::Vec3 eye = {0.0f, 0.0f, 5.0f};

    float view_mat[16];
    bx::mtxLookAt(view_mat, eye, at);

    float proj_mat[16];
    bx::mtxProj(proj_mat, 
                60.0f,
                float(window_size.x) / float(window_size.y),
                0.1f,
                100.0f,
                bgfx::getCaps()->homogeneousDepth);

    // add performance metrics
    bgfx::setDebug(BGFX_DEBUG_TEXT);
}

Renderer::~Renderer() {
    bgfx::shutdown();
}

void Renderer::drawFrame(SceneManager& scene_mngr, std::chrono::duration<double> delta)
{
    auto wsize = window_mngr.getSize();

    Matrix4f view_mtx;
    Matrix4f proj_mtx;
    
    auto cam_entity = scene_mngr.camera();

    if (cam_entity == entt::null) {
        const bx::Vec3 at_ = {0.0f, 0.0f, 0.0f};
        const bx::Vec3 eye_ = {0.0f, 0.0f, -5.0f};
        bx::mtxLookAt(view_mtx, eye_, at_);
        bx::mtxProj(proj_mtx,
                    60.0f,
                    float(wsize.x) / float(wsize.y),
                    0.1f,
                    100.0f,
                    bgfx::getCaps()->homogeneousDepth);
    
    } else {
        auto camera_transform = scene_mngr.registry().get<SceneGraphNode>(cam_entity);

        bx::Vec3 aux {0.0f, 0.0f, 0.0f};
        auto eye = bx::mul(aux, camera_transform.transformMatrix());

        aux = {0.0f, 0.0f, 1.0f};
        auto at = bx::mul(aux, camera_transform.transformMatrix());

        bx::mtxLookAt(view_mtx, eye, at);

        const auto& camera_comp = scene_mngr.registry().get<CameraComponent>(cam_entity);
        bx::mtxProj(proj_mtx, 
                    camera_comp.fovy,
                    float(wsize.x) / float(wsize.y),
                    camera_comp.near,
                    camera_comp.far,
                    bgfx::getCaps()->homogeneousDepth);
    }
    
    bgfx::touch(view_id);

    auto reg_view = scene_mngr.registry().view<SceneGraphNode, const VisualComponent>();
    reg_view.each(
            [this, wsize, view_mtx, proj_mtx]
            (const auto entity, SceneGraphNode& transform, const VisualComponent& visual)
        {
            bgfx::setViewRect(view_id, 0, 0, wsize.x, wsize.y);
            bgfx::setViewTransform(view_id, view_mtx, proj_mtx);

            auto mesh = visual.visual->getMesh();
            bgfx::setVertexBuffer(view_id, mesh->vb);
            bgfx::setIndexBuffer(mesh->ib);

            // transform
            bgfx::setTransform(transform.transformMatrix());

            bgfx::submit(view_id, visual.visual->getMaterial()->getShader()->handle);
        }
    );

    bgfx::frame();
}

void Renderer::drawPerfMon(const PerformanceMonitor& perf_monitor,
                           DeltaClock::milliseconds_double delta) noexcept
{
    std::chrono::duration<float> hertz {delta};
    bgfx::dbgTextPrintf(1, 0, 0xf0, "FPS=%5.1f          Delta=%8.6fms", 1/hertz.count(),  delta.count());

    for (int i = 0; i < perf_monitor.size(); ++i) {
        auto& item = perf_monitor.getItem(i);
        bgfx::dbgTextPrintf(1, i + 1, 0x0f, "%-20s : %10.6fms", item.label, item.delta.count());
    }
}

} // namespace folk