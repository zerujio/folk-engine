#include "folk/render/visual_component.hpp"

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

struct PosColorVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
	4, 6, 5,
	5, 6, 7,
	0, 2, 4,
	4, 2, 6,
	1, 5, 3,
	5, 7, 3,
	0, 4, 1,
	4, 5, 1,
	2, 3, 6,
	6, 3, 7,
};

struct DebugGeometry {
    bgfx::VertexBufferHandle vb;
    bgfx::IndexBufferHandle ib;
    bgfx::ProgramHandle program;
    bgfx::VertexLayout layout;

    float model[16];
    float view[16];
    float proj[16];
};

DebugGeometry dbg_geom;

namespace Folk {

Renderer::Renderer()
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

    // bgfx_init.type = bgfx::RendererType::OpenGL;

    if (!bgfx::init(bgfx_init))
        throw CriticalEngineError("bgfx initialization failed");

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

    // DEBUG GEOMETRY
    dbg_geom.layout.begin()
                         .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                         .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
                         .end();
    dbg_geom.vb = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, 
                                                         sizeof(cubeVertices)),
                                           dbg_geom.layout);
    dbg_geom.ib = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

    
    bgfx::ShaderHandle vsh = loadShaderFile("vs_basic.bin");
    bgfx::ShaderHandle fsh = loadShaderFile("fs_basic.bin");
    dbg_geom.program = buildProgram(vsh, fsh);

    const bx::Vec3 at_ = {0.0f, 0.0f, 0.0f};
    const bx::Vec3 eye_ = {0.0f, 0.0f, -5.0f};
    bx::mtxLookAt(dbg_geom.view, eye_, at_);
    bx::mtxProj(dbg_geom.proj, 60.0f, float(wsize.width) / float(wsize.height),
                0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
    // DEBUG
}

Renderer::~Renderer() {
    //  DEBUG
    bgfx::destroy(dbg_geom.vb);
    bgfx::destroy(dbg_geom.ib);
    bgfx::destroy(dbg_geom.program);
    //  DEBUG
    bgfx::shutdown();
}

void Renderer::update(Delta delta)
{
    ENGINE.perf_monitor.start(perf_monitor_id);

    bgfx::setViewTransform(view_id, view_mat, proj_mat);

    auto& wsize = WINDOW.getWindowSize();
    bgfx::setViewRect(view_id, 0, 0, wsize.width, wsize.height);

    bgfx::touch(view_id);

    auto view = SCENE.registry.view<VisualComponent>();
    view.each([this](const auto entity, VisualComponent& component) 
        {   
            auto mesh = component.visual->getMesh();
            auto mesh_data = static_cast<MeshData*>(mesh.get());

            bgfx::setVertexBuffer(view_id, mesh_data->vb_handle);
            bgfx::setIndexBuffer(mesh_data->ib_handle);

            float transform[16];
            bx::mtxTranslate(transform, 0, 0, 0);
            bgfx::setTransform(transform);

            auto shader = component.visual->getMaterial()->getShader();
            auto shader_data = static_cast<ShaderData*>(shader.get());

            bgfx::setState(BGFX_STATE_DEFAULT);
            // bgfx::submit(view_id, shader_data->program_handle);
        }
    );
    
    ENGINE.perf_monitor.draw();

    ENGINE.perf_monitor.stop(perf_monitor_id);

    //  DEBUG

    static float angle = 0.0f;
    angle += delta.count();
    bx::mtxRotateXY(dbg_geom.model, angle, -angle);

    bgfx::setViewTransform(view_id, dbg_geom.view, dbg_geom.proj);
    bgfx::setTransform(dbg_geom.model);
    bgfx::setVertexBuffer(view_id, dbg_geom.vb);
    bgfx::setIndexBuffer(dbg_geom.ib);
    bgfx::submit(view_id, dbg_geom.program);

    //  DEBUG

    bgfx::dbgTextPrintf(80, 0, 0x0f, "DELTA=%f", delta.count());

    bgfx::frame();
}

} // namespace folk