#include "window_manager.hpp"

#include "../core/engine_singleton.hpp"

#include "folk/core/error.hpp"

#include <sstream>

namespace Folk {

static void closeWindowCallback(GLFWwindow*);
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, 
                                GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam);
void glfwErrorCallback(int, const char*);

WindowManager::WindowManager() 
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
        throw FOLK_RUNTIME_ERROR("GLFW initialization failed.");

    /* 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version.minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    */
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(
        window_size.width, 
        window_size.height, 
        window_title.c_str(),
        nullptr,
        nullptr);
    
    if (window == nullptr) {
        glfwTerminate();
        throw FOLK_RUNTIME_ERROR("GLFW: window creation failed.");
    }

    glfwSetWindowCloseCallback(window, closeWindowCallback);

    // glfwMakeContextCurrent(window);

    /* 
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw CriticalEngineError("OpenGL context initialization error: "
                                "gladLoadGLLoader returned an error");
    
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, 0); 
    */
}

WindowManager::~WindowManager() 
{
    glfwTerminate();
}

void WindowManager::setWindowTitle(const char* title)
{
    window_title = title;
    glfwSetWindowTitle(window, window_title.c_str());
}

GLFWwindow* WindowManager::windowPtr() 
{
    return window;
}

WindowManager::WindowDimentions const& WindowManager::getWindowSize() 
{
    glfwGetWindowSize(window, &window_size.width, &window_size.height);

    return window_size;
}

void WindowManager::update(Delta delta) {
    try {
        glfwPollEvents();
    } catch (...) {
        ENGINE.exception.handle();
    }
}

static void closeWindowCallback(GLFWwindow *w)
{
    ENGINE.exit();
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
    Log::Level log_level;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        severity_str = "HIGH";
        log_level = Log::Level::ERROR;
        break;
    
    case GL_DEBUG_SEVERITY_MEDIUM:
        severity_str = "MEDIUM";
        log_level = Log::Level::WARNING;
        break;
    
    case GL_DEBUG_SEVERITY_LOW:
        severity_str = "LOW";
        log_level = Log::Level::WARNING;
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity_str = "NOTIFICATION";
        log_level = Log::Level::MESSAGE;
        break;
    
    default:
        severity_str = "?";
        log_level = Log::Level::MESSAGE;
        break;
    }
    
    ENGINE.log.begin(log_level) << "*** OpenGL DEBUG MESSAGE ***"
                                << "\nsource    : " << source_str
                                << "\ntype      : " << type_str
                                << "\nseverity  : " << severity_str
                                << '\n' << message << "\n\n";
}

void glfwErrorCallback(int code, const char* message) {
    std::stringstream exc_msg;

    exc_msg << "GLFW error " << code << " : " << message;

    try {
        throw FOLK_RUNTIME_ERROR(exc_msg.str());
    } catch (...) {
        ENGINE.exception.handle();
    }
}

} // namespace folk