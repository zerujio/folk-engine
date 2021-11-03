#include "folk/render/visual_component.hpp"
#include "../core/engine_singleton.hpp"
#include "../window/window_manager.hpp"

#include "common.hpp"
#include "renderer.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

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

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(WINDOW.windowPtr(), true);
    ImGui_ImplOpenGL3_Init("#version 430");

    // add performance metrics
    perf_monitor_id = ENGINE.perf_monitor.addItem("Renderer (CPU)");
}

Renderer::~Renderer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    bgfx::shutdown();
}


void Renderer::update(Delta delta)
{
    ENGINE.perf_monitor.start(perf_monitor_id);

    bgfx::touch(view_id);

    auto view = SCENE.registry.view<VisualComponent>();

    bgfx::setViewTransform(view_id, view_mat, proj_mat);

    view.each([this](const auto entity, VisualComponent& component) 
        {
            auto& mesh_data = RENDER.meshes.at(component.visual->mesh->id);
            auto& shader_data = RENDER.shaders.at(component.visual->material->shader->id);

            float transform[16];
            bx::mtxTranslate(transform, 0, 0, 0);

            bgfx::setTransform(transform);
            bgfx::setState(BGFX_STATE_DEFAULT);
            bgfx::submit(view_id, shader_data.program_handle);
        }
    );
    
    // Draw ImGUI things
    imguiDraw();

    ENGINE.perf_monitor.stop(perf_monitor_id);

    bgfx::frame();
}

void Renderer::imguiDraw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ENGINE.perf_monitor.draw();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace folk