#include "folk/render/visual_component.hpp"
#include "../core/engine_singleton.hpp"
#include "../window/module.hpp"
#include "module.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Folk {

RenderModule::RenderModule() 
{
    {
        auto& wsize = WINDOW.getWindowSize();
        glViewport(0, 0, wsize.width, wsize.height);
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

static void glDump() {
    GLint vao, vbo, ebo, program;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &vbo);
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &ebo);
    glGetIntegerv(GL_CURRENT_PROGRAM, &program);
    /* 
    ENGINE.out << "*** OPENGL STATE DUMP ***\n"
        << "VAO=" << vao << "\n"
        << "VBO=" << vbo << "\n"
        << "EBO=" << ebo << "\n"
        << "Program=" << program << "\n";
     */
}

void RenderModule::update(Delta delta)
{
    glClear(GL_COLOR_BUFFER_BIT);

    auto view = ENGINE.scene.scene._registry.view<VisualComponent>();

    static bool once = true;

    view.each([](const auto entity, VisualComponent& component) 
        {
            glUseProgram(component.visual->material->program);
            glBindVertexArray(component.visual->vao);
            glDrawElements(
                GL_TRIANGLES, component.visual->mesh->index_count,
                GL_UNSIGNED_INT, 0);

            if (once) {
                glDump();
                once = false;
            }
        }
    );
    glBindVertexArray(0);

    glfwSwapBuffers(WINDOW.getWindowPtr());
}

} // namespace folk