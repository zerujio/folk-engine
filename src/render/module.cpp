#include <glad/glad.h>
#include "../window/module.hpp"
#include "module.hpp"

namespace folk {

RenderModule::RenderModule() 
{
    glfwMakeContextCurrent(WINDOW.getWindowPtr());

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw CriticalEngineError("OpenGL context initialization error: gladLoadGLLoader returned an error");

    {
        auto& wsize = WINDOW.getWindowSize();
        glViewport(0, 0, wsize.width, wsize.height);
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void RenderModule::update(Delta delta)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(WINDOW.getWindowPtr());
}

} // namespace folk