//
// Created by sergio on 01-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_CALL_HPP
#define INCLUDE_FOLK_RENDER__GL_CALL_HPP

#ifndef FOLK_DEBUG

#define #define FOLK_GL_CALL(function, ...) function(##__VA_ARGS__)

#else // FOLK_DEBUG

#include "gl.hpp"
#include "folk/utils/library_call.hpp"

#include <type_traits>

namespace Folk::gl {

const char* errorString(GLenum error) noexcept;

std::optional<const char*> getError() noexcept;

using call = LibCall<getError>;

void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

} // namespace Folk::gl

#endif // FOLK_DEBUG

#endif //INCLUDE_FOLK_RENDER__GL_CALL_HPP