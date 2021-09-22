#include "folk/engine/error.hpp"
#include "../engine/engine_singleton.hpp"
#include "module.hpp"

namespace folk {

static void closeWindowCallback(GLFWwindow *w)
{
    ENGINE.exit();
}

void WindowModule::onStartUp() 
{
    if (!glfwInit())
        throw EngineRuntimeError("GLFW initialization failed.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(
        window_size.width, 
        window_size.height, 
        window_title.c_str(),
        nullptr,
        nullptr);
    
    if (window == nullptr) {
        glfwTerminate();
        throw EngineRuntimeError("GLFW: window creation failed.");
    }
    
    glfwMakeContextCurrent(window);

    glfwSetWindowCloseCallback(window, closeWindowCallback);
}

void WindowModule::onShutDown() 
{
    glfwTerminate();
}

void WindowModule::setWindowTitle(const char* title)
{
    window_title = title;

    if (isRunning())
        glfwSetWindowTitle(window, window_title.c_str());
}

GLFWwindow* WindowModule::getWindowPtr() 
{
    return window;
}

WindowModule::WindowDimentions const& WindowModule::getWindowSize() 
{
    return window_size;
}

} // namespace folk