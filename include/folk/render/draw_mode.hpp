//
// Created by sergio on 06-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__DRAW_MODE_HPP
#define INCLUDE_FOLK_RENDER__DRAW_MODE_HPP

#include "gl.hpp"

namespace Folk {

/// OpenGL draw modes
enum class DrawMode : GLenum {
    Triangles = GL_TRIANGLES,
    Lines = GL_LINES,
};

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__DRAW_MODE_HPP
