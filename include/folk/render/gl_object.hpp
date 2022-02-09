//
// Created by sergio on 07-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_OBJECT_HPP
#define INCLUDE_FOLK_RENDER__GL_OBJECT_HPP

#include "gl.hpp"
#include "folk/utils/object_handle.hpp"
#include "folk/utils/object_manager.hpp"

namespace Folk::gl {

template<auto isValid>
using BaseHandle = ObjectHandle<call, isValid, GLuint>;

} // namespace Folk::gl

#endif //INCLUDE_FOLK_RENDER__GL_OBJECT_HPP
