//
// Created by sergio on 05-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_HANDLE_HPP
#define INCLUDE_FOLK_RENDER__GL_HANDLE_HPP

#include "gl_call.hpp"
#include "../utils/object_handle.hpp"

namespace Folk::gl {

template<auto isValid>
using BaseHandle = ObjectHandle<call, isValid, GLuint>;

} // namespace Folk::gl

#endif //INCLUDE_FOLK_RENDER__GL_HANDLE_HPP
