#include "folk/error.hpp"
#include "module.hpp"
#include "../engine/engine_singleton.hpp"

namespace folk {

static void closeWindowCallback(GLFWwindow*);
static void keyCallback(GLFWwindow*, int, int, int, int);

WindowModule::WindowModule() 
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

    glfwSetWindowCloseCallback(window, closeWindowCallback);
    glfwSetKeyCallback(window, keyCallback);
}

WindowModule::~WindowModule() 
{
    glfwTerminate();
}

void WindowModule::setWindowTitle(const char* title)
{
    window_title = title;
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

void WindowModule::update(double delta) {
    glfwPollEvents();
}

static void closeWindowCallback(GLFWwindow *w)
{
    ENGINE.exit();
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        try {
            switch (key) {
                case GLFW_KEY_ESCAPE:
                    throw CriticalEngineError("dummy critical error");
                    break;
                case GLFW_KEY_SPACE:
                    throw EngineRuntimeError("dummy engine runtime error");
                    break;
            }
        } catch (...) {
            ENGINE.transportException(std::current_exception());
        }
    }
}

} // namespace folk