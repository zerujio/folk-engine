#include "folk/core/error.hpp"

#include "module.hpp"

#include "../core/common.hpp"
#include "../core/engine_singleton.hpp"

namespace Folk {

static void closeWindowCallback(GLFWwindow*);
static void keyCallback(GLFWwindow*, int, int, int, int);
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, 
                                GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam);

WindowModule::WindowModule() 
{
    if (!glfwInit())
        throw EngineRuntimeError("GLFW initialization failed.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version.minor);
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

    glfwMakeContextCurrent(WINDOW.getWindowPtr());

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw CriticalEngineError("OpenGL context initialization error: "
                                "gladLoadGLLoader returned an error");
    
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, 0);
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

void WindowModule::update(Delta delta) {
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
            ENGINE.exception.handle();
            // ENGINE.transportException(std::current_exception());
        }
    }
}

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, 
                                GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam)
{
    const char* source_str; 
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        source_str = "API";
        break;
    
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source_str = "WINDOW_SYSTEM";
        break;
    
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source_str = "SHADER_COMPILER";
        break;
    
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source_str = "THIRD_PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        source_str = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        source_str = "OTHER";
        break;
    
    default:
        source_str = "?";
        break;
    }

    const char* type_str;
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        type_str = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type_str = "DEPRECATED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type_str = "UNDEFINED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        type_str = "PORTABILITY";
        break; 

    case GL_DEBUG_TYPE_PERFORMANCE:
        type_str = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        type_str = "OTHER";
        break;

    default:
        type_str = "?";
        break;
    }

    const char* severity_str;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        severity_str = "HIGH";
        break;
    
    case GL_DEBUG_SEVERITY_MEDIUM:
        severity_str = "MEDIUM";
        break;
    
    case GL_DEBUG_SEVERITY_LOW:
        severity_str = "LOW";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity_str = "NOTIFICATION";
        break;
    
    default:
        severity_str = "?";
        break;
    }

    std::string msg = 
        std::string("*** GL DEBUG MESSAGE ***\n")
        + "source:     " + source_str + "\n"
        + "type:       " + type_str + "\n"
        + "severity:   " + severity_str + "\n"
        + message + "\n\n";

    try {
        throw EngineRuntimeError(msg);
    }
    catch(...)
    {
        ENGINE.exception.handle();
    }
}

} // namespace folk