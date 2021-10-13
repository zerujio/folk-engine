#ifndef FOLK_RENDER__COMMON_HPP
#define FOLK_RENDER__COMMON_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

namespace Folk {

using Coord = GLfloat;
using Index = GLuint;

using VertexArray = std::vector<Coord>;
using IndexArray = std::vector<Index>;

}

#endif//FOLK_RENDER__COMMON_HPP

