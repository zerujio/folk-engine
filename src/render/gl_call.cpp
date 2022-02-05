//
// Created by sergio on 02-02-22.
//

#ifdef FOLK_DEBUG

#include "folk/render/gl_call.hpp"
#include "folk/render/gl.hpp"
#include "folk/log.hpp"

namespace Folk {

const char* gl::errorString(GLenum error) noexcept
{
    switch (error) {
        case GL_NO_ERROR:
            return "NO_ERROR";
        case GL_INVALID_ENUM:
            return "INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "INVALID_FRAME_BUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:
            return "STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "STACK_OVERFLOW";
        default:
            return "<unknown error>";
    }
}

std::optional<const char *> gl::getError() noexcept {
    auto err = glGetError();
    if (err)
        return {errorString(err)};
    else
        return {};
}

constexpr const char *errorSourceString(GLenum source) noexcept {
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            return "API";

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "WINDOW_SYSTEM";

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "SHADER_COMPILER";

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "THIRD_PARTY";

        case GL_DEBUG_SOURCE_APPLICATION:
            return "APPLICATION";

        case GL_DEBUG_SOURCE_OTHER:
            return "OTHER";

        default:
            return "<invalid>";
    }
}

constexpr const char *errorTypeString(GLenum type) noexcept {
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            return "ERROR";

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "DEPRECATED_BEHAVIOR";

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "UNDEFINED_BEHAVIOR";

        case GL_DEBUG_TYPE_PORTABILITY:
            return "PORTABILITY";

        case GL_DEBUG_TYPE_PERFORMANCE:
            return "PERFORMANCE";

        case GL_DEBUG_TYPE_OTHER:
            return "OTHER";

        default:
            return "<invalid>";
    }
}

constexpr const char *errorSeverityString(GLenum severity) noexcept {
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            return "HIGH";

        case GL_DEBUG_SEVERITY_MEDIUM:
            return "MEDIUM";

        case GL_DEBUG_SEVERITY_LOW:
            return "LOW";

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "NOTIFICATION";

        default:
            return "<invalid>";
    }
}

void GLAPIENTRY gl::debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                         const GLchar* message, const void* userParam)
{
    LogLevel log_level;
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            log_level = LogLevel::Error;
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            log_level = LogLevel::Warning;
            break;
        case GL_DEBUG_SEVERITY_LOW:
            log_level = LogLevel::Message;
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            log_level = LogLevel::Trace;
            break;
        default:
            log_level = LogLevel::Warning;
            break;
    }

    Log::write(log_level) << "*** OpenGL DEBUG MESSAGE ***"
                          << "\nsource      : " << errorSourceString(source)
                          << "\ntype        : " << errorTypeString(type)
                          << "\nseverity    : " << errorSeverityString(severity)
                          << "\ndescription : " << message
                          << "\n\n";
}

} // namespace Folk::gl

#endif // GL_DEBUG
