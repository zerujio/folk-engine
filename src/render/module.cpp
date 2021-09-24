#include <glad/glad.h>
#include "../window/module.hpp"
#include "module.hpp"

namespace folk {

// RenderModule::RenderThread
RenderModule::RenderThread::RenderThread()
{   
    {
        std::unique_lock m(mutex);
        
        thread = std::thread(&RenderThread::main, this);

        while (status != STOPPED)
            condition.wait(m);
    }

    if (status == ERROR) {
        thread.join();
        throw EngineRuntimeError("OpenGL context initialization failed");
    }
}

RenderModule::RenderThread::~RenderThread()
{
    {
        std::lock_guard m(mutex);
        stop_flag = true;
    }

    thread.join();
}

void RenderModule::RenderThread::main()
{
    bool success = configureContext();

    {
        std::lock_guard lk(mutex);

        if (success) {
            status = STARTED;
        } else {
            status = ERROR;
        }
    }

    condition.notify_all();

    if (success)
        renderLoop();
}

bool RenderModule::RenderThread::configureContext()
{
    glfwMakeContextCurrent(WINDOW.getWindowPtr());

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        return false;

    {
        auto& wsize = WINDOW.getWindowSize();
        glViewport(0, 0, wsize.width, wsize.height);
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    
    return true;
}

void RenderModule::RenderThread::renderLoop()
{
    while(!checkStopFlag()) {
        //GLFW
        glfwPollEvents();
        //OpenGL
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(WINDOW.getWindowPtr());
    }
}

bool RenderModule::RenderThread::checkStopFlag()
{
    std::lock_guard lk(mutex);
    return stop_flag;
}

} // namespace folk