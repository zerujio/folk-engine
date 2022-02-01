#include "folk/window/window_manager.hpp"

#include "folk/core/engine.hpp"

namespace Folk {

WindowManager::WindowManager(const char* window_name)
{
    m_window_ptr = FOLK_GLFW_CALL(glfwCreateWindow, s_default_window_size.x, s_default_window_size.y, window_name, nullptr, nullptr);
}

WindowManager::WindowManager(const std::string &window_name) : WindowManager(window_name.c_str()) {}

WindowManager::WindowManager(WindowManager &&other) noexcept : m_window_ptr(other.m_window_ptr) {
    other.m_window_ptr = nullptr;
}

WindowManager &WindowManager::operator=(WindowManager &&other) noexcept {
    if (m_window_ptr)
        destroyWindow();

    m_window_ptr = other.m_window_ptr;
    other.m_window_ptr = nullptr;

    return *this;
}

WindowManager::~WindowManager() {
    if (m_window_ptr)
        destroyWindow();
}

void WindowManager::destroyWindow() {
    FOLK_GLFW_CALL(glfwDestroyWindow, m_window_ptr);
    m_window_ptr = nullptr;
}

WindowManager::operator bool() const {
    return m_window_ptr;
}

bool WindowManager::isNull() const {
    return !m_window_ptr;
}

void WindowManager::setTitle(const char *title) const {
    FOLK_GLFW_CALL(glfwSetWindowTitle, m_window_ptr, title);
}

void WindowManager::setTitle(const std::string &title) const {
    setTitle(title.c_str());
}

void WindowManager::setSize(Vec2i size) const {
    FOLK_GLFW_CALL(glfwSetWindowSize, m_window_ptr, size.x, size.y);
}

Vec2i WindowManager::getSize() const {
    int x, y;
    FOLK_GLFW_CALL(glfwGetWindowSize, m_window_ptr, &x, &y);
    return {x, y};
}

GLFWwindow *WindowManager::handle() const {
    return m_window_ptr;
}

void WindowManager::clearCloseCallback() const {
    FOLK_GLFW_CALL(glfwSetWindowCloseCallback, m_window_ptr, nullptr);
}

#if 0
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
    LogLevel log_level;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        severity_str = "HIGH";
        log_level = LogLevel::Error;
        break;
    
    case GL_DEBUG_SEVERITY_MEDIUM:
        severity_str = "MEDIUM";
        log_level = LogLevel::Warning;
        break;
    
    case GL_DEBUG_SEVERITY_LOW:
        severity_str = "LOW";
        log_level = LogLevel::Warning;
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity_str = "NOTIFICATION";
        log_level = LogLevel::Message;
        break;
    
    default:
        severity_str = "?";
        log_level = LogLevel::Message;
        break;
    }

    Log::write(log_level) << "*** OpenGL DEBUG MESSAGE ***"
                                << "\nsource    : " << source_str
                                << "\ntype      : " << type_str
                                << "\nseverity  : " << severity_str
                                << '\n' << message << "\n\n";
}
#endif

} // namespace folk