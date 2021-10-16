#include "folk/render/visual_component.hpp"
#include "../core/engine_singleton.hpp"
#include "../window/module.hpp"

#include "common.hpp"
#include "module.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Folk {

RenderModule::RenderModule() 
{
    {
        auto& wsize = WINDOW.getWindowSize();
        glViewport(0, 0, wsize.width, wsize.height);
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(WINDOW.getWindowPtr(), true);
    ImGui_ImplOpenGL3_Init("#version 430");

    // add performance metrics
    render_id = ENGINE.perf_monitor.addItem("Rendering");
    frame_time_id = ENGINE.perf_monitor.addItem("Effective frame time");

}

RenderModule::~RenderModule() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void RenderModule::update(Delta delta)
{
    ENGINE.perf_monitor.stop(frame_time_id);
    ENGINE.perf_monitor.start(frame_time_id);

    ENGINE.perf_monitor.start(render_id);

    glClear(GL_COLOR_BUFFER_BIT);

    auto view = SCENE.registry.view<VisualComponent>();

    static bool once = true;

    view.each([](const auto entity, VisualComponent& component) 
        {
            auto& visual_data = RENDER.visuals.at(component.visual->id);
            auto& mesh_data = RENDER.meshes.at(component.visual->mesh->id);
            auto& shader_data = RENDER.shaders.at(component.visual->material->shader->id);

            glUseProgram(shader_data.program);
            glBindVertexArray(visual_data.vao);
            glDrawElements(GL_TRIANGLES, mesh_data.count, GL_UNSIGNED_INT, 0);
        }
    );
    glBindVertexArray(0);

    // Draw ImGUI things
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ENGINE.perf_monitor.draw();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ENGINE.perf_monitor.stop(render_id);

    glfwSwapBuffers(WINDOW.getWindowPtr());
}

} // namespace folk