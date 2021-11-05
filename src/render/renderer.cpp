#include "folk/render/visual_component.hpp"
#include "../core/engine_singleton.hpp"
#include "../window/window_manager.hpp"

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

// debug geometry

struct PosColorVertex {
  float m_x;
  float m_y;
  float m_z;
  uint32_t m_abgr;

  static void init() {
    ms_decl
      .begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
      .end();
  };

  static bgfx::VertexLayout ms_decl;
};

bgfx::VertexLayout PosColorVertex::ms_decl {};

static PosColorVertex s_cubeVertices[] =
{
    {  0.5f,  0.5f, 0.0f, 0xff0000ff },
    {  0.5f, -0.5f, 0.0f, 0xff0000ff },
    { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
    { -0.5f,  0.5f, 0.0f, 0xff00ff00 }
};

static const uint16_t s_cubeTriList[] =
  {
   0,1,3,
   1,2,3
  };

bgfx::VertexBufferHandle m_vbh;
bgfx::IndexBufferHandle m_ibh;

bgfx::ProgramHandle m_program;

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

    bgfx_init.type = bgfx::RendererType::OpenGL;

    if (!bgfx::init(bgfx_init))
        throw CriticalEngineError("bgfx initialization failed");

    // view_id = 0;
	bgfx::setViewClear(view_id, BGFX_CLEAR_COLOR);
	bgfx::setViewRect(view_id, 0, 0, bgfx::BackbufferRatio::Equal);

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

    PosColorVertex::init();
    
    /* DEBUG */
    m_vbh = bgfx::createVertexBuffer(
        bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
        PosColorVertex::ms_decl
    );

    m_ibh = bgfx::createIndexBuffer(
        bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
    );
    
    m_program = getDefaultProgramHandle();
}

Renderer::~Renderer() {
    // DEBUG
    bgfx::destroy(m_vbh);
    bgfx::destroy(m_ibh);
    bgfx::destroy(m_program);
    // DEBUG

    bgfx::shutdown();
}

void Renderer::update(Delta delta)
{
    ENGINE.perf_monitor.start(perf_monitor_id);

    bgfx::touch(view_id);
    bgfx::setViewTransform(view_id, view_mat, proj_mat);

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
            bgfx::submit(view_id, shader_data->program_handle);
        }
    );

    /* DEBUG */
    float dbg_transform[16];
    bx::mtxRotateY(dbg_transform, 0.0f);
    dbg_transform[12] = 0.0f;
    dbg_transform[13] = 0.0f;
    dbg_transform[14] = 0.0f;

    bgfx::setVertexBuffer(view_id, m_vbh);
    bgfx::setIndexBuffer(m_ibh);
    bgfx::submit(view_id, m_program);

    /* DEBUG */
    
    ENGINE.perf_monitor.draw();

    ENGINE.perf_monitor.stop(perf_monitor_id);

    bgfx::frame();
}

} // namespace folk