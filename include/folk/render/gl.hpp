//
// Created by sergio on 02-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_HPP
#define INCLUDE_FOLK_RENDER__GL_HPP

#include "folk/window/glfw.hpp"
#include "folk/error.hpp"
#include "folk/utils/library_call.hpp"

namespace Folk::gl {

const char* errorString(GLenum error) noexcept;

struct GLError : public Error {
    using Error::Error;

    template<class... Args>
    explicit GLError(GLenum code, Args&&... args) : Error(errorString(code), args...) {}
};

GLenum getError() noexcept;

using call = LibCall<GLError, getError>;

} // namespace Folk::gl

#endif //INCLUDE_FOLK_RENDER__GL_HPP
