#include "folk/render/visual_component.hpp"
#include "folk/scene/transform_component.hpp"

#include "../core/engine_singleton.hpp"
#include "../window/window_manager.hpp"
#include "../render/shader_loader.hpp"


#include "common.hpp"
#include "renderer.hpp"
#include "default_shader.hpp"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace Folk {

Renderer::Renderer(Log& log, ExceptionHandler& exc) : bgfx_callback_handler(log, exc)
{
    // bgfx
    bgfx::renderFrame();

    bgfx::Init bgfx_init;
    bgfx_init.platformData.ndt = glfwGetX11Display();
    bgfx_init.platformData.nwh = (void*)(uintptr_t) glfwGetX11Window(WINDOW.windowPtr());

    auto wsize = WINDOW.getWindowSize();
    bgfx_init.resolution.width = wsize.width;
    bgfx_init.resolution.height = wsize.height;
    bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx_init.callback = &bgfx_callback_handler;

    // bgfx_init.type = bgfx::RendererType::OpenGL;

    if (!bgfx::init(bgfx_init))
        throw FOLK_CRITICAL_ERROR("bgfx initialization failed");

    // view_id = 0;
	bgfx::setViewClear(view_id, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
	bgfx::setViewRect(view_id, 0, 0, wsize.width, wsize.height);

    const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
    const bx::Vec3 eye = {0.0f, 0.0f, 5.0f};

    float view_mat[16];
    bx::mtxLookAt(view_mat, eye, at);

    float proj_mat[16];
    bx::mtxProj(proj_mat, 
                60.0f, 
                float(wsize.width)/float(wsize.height),
                0.1f,
                100.0f,
                bgfx::getCaps()->homogeneousDepth);

    // add performance metrics
    perf_monitor_id = ENGINE.perf_monitor.addItem("Renderer (CPU)");
}

Renderer::~Renderer() {
    bgfx::shutdown();
}

void Renderer::update(Delta delta)
{
    ENGINE.perf_monitor.start(perf_monitor_id);

    auto& wsize = WINDOW.getWindowSize();

    Matrix4f view_mtx;
    Matrix4f proj_mtx;
    
    auto cam_entity = SCENE.scene.m_camera;

    if (cam_entity == entt::null) {
        const bx::Vec3 at_ = {0.0f, 0.0f, 0.0f};
        const bx::Vec3 eye_ = {0.0f, 0.0f, -5.0f};
        bx::mtxLookAt(view_mtx, eye_, at_);
        bx::mtxProj(proj_mtx,
                    60.0f,
                    float(wsize.width) / float(wsize.height),
                    0.1f,
                    100.0f,
                    bgfx::getCaps()->homogeneousDepth);
    
    } else {
        auto camera_transform = SCENE.scene.m_registry.get<SceneGraphNode>(cam_entity);

        bx::Vec3 aux {0.0f, 0.0f, 0.0f};
        auto eye = bx::mul(aux, camera_transform.transformMatrix());

        aux = {0.0f, 0.0f, 1.0f};
        auto at = bx::mul(aux, camera_transform.transformMatrix());

        bx::mtxLookAt(view_mtx, eye, at);

        auto camera_comp = SCENE.scene.getCamera();
        bx::mtxProj(proj_mtx, 
                    camera_comp.fovy(),
                    float(wsize.width) / float(wsize.height),
                    camera_comp.near(),
                    camera_comp.far(),
                    bgfx::getCaps()->homogeneousDepth);
    }
    
    bgfx::touch(view_id);

    auto reg_view = SCENE.scene.m_registry.view<SceneGraphNode, VisualComponent>();
    reg_view.each([this, wsize, view_mtx, proj_mtx](const auto entity,
                                                    SceneGraphNode& transform,
                                                    const VisualComponent& visual)
        {
            bgfx::setViewRect(view_id, 0, 0, wsize.width, wsize.height);
            bgfx::setViewTransform(view_id, view_mtx, proj_mtx);

            auto mesh = visual.visual->getMesh();
            bgfx::setVertexBuffer(view_id, mesh->vb);
            bgfx::setIndexBuffer(mesh->ib);

            // transform
            bgfx::setTransform(transform.transformMatrix());

            bgfx::submit(view_id, visual.visual->getMaterial()->getShader()->handle);
        }
    );
    
    ENGINE.perf_monitor.draw();

    ENGINE.perf_monitor.stop(perf_monitor_id);

    bgfx::dbgTextPrintf(80, 0, 0x0f, "DELTA=%f", delta.count());

    bgfx::frame();
}

BGFXCallbackHandler::BGFXCallbackHandler(Log& log, ExceptionHandler& exc) 
    : m_log(log), m_handler(exc)
{}

void BGFXCallbackHandler::fatal(const char* file_path, 
                                uint16_t line, 
                                bgfx::Fatal::Enum code, 
                                const char* description)
{
    m_log.begin(LogLevel::ERROR) 
        << file_path << ": " << line << " | " << std::hex << code;
    
    if (code == bgfx::Fatal::Enum::DebugCheck)
        bx::debugBreak(); // quien sabe qué hace esto!

    m_handler.throwException<CriticalError>(description, FOLK_HERE_ARGS);
}

void BGFXCallbackHandler::traceVargs(const char* file_path, 
                                    uint16_t line,
                                    const char* format,
                                    va_list arg_list)
{
    constexpr std::size_t buflen = 2048;
    char temp[buflen];

    std::vsnprintf(temp, buflen, format, arg_list);

    m_log.begin(LogLevel::TRACE)
        << file_path << ": " << line << " | " << temp;
}

void BGFXCallbackHandler::screenShot(const char* file_path, 
                                    uint32_t width, 
                                    uint32_t height,
                                    uint32_t pitch, 
                                    const void* data, 
                                    uint32_t size, 
                                    bool yflip)
{
    m_log.begin(LogLevel::WARNING) << "BGFX screenShot used but not implemented";
}

void BGFXCallbackHandler::captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, 
                    bgfx::TextureFormat::Enum _format, bool _yflip)
{
    m_log.begin(LogLevel::WARNING) << "BGFX captureBegin used but not implemented";
}

void BGFXCallbackHandler::captureEnd() {}

void BGFXCallbackHandler::captureFrame(const void *_data, uint32_t _size) {
    m_log.begin(LogLevel::WARNING) << "BGFX captureFrame used but not implemented";
}

} // namespace folk