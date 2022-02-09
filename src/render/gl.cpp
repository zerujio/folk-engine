//
// Created by sergio on 02-02-22.
//

#ifdef FOLK_DEBUG

#include "folk/render/gl.hpp"

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

GLenum gl::getError() noexcept {
    return glGetError();
}

} // namespace Folk::gl

#endif // GL_DEBUG
