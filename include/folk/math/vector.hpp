#ifndef FOLK_UTILS__VECTOR_HPP
#define FOLK_UTILS__VECTOR_HPP

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

namespace Folk
{

/// 4 element floating point vector.
using Vec4 = glm::vec4;

/// 4 element integer vector
using Vec4i = glm::ivec4;

/// 3 element floating point vector.
using Vec3 = glm::vec3;

/// 3 element integer vector.
using Vec3i = glm::ivec3;

/// 2 element floating point vector.
using Vec2 = glm::vec2;

/// 2 element double precision floating point vector.
using Vec2d = glm::dvec2;

/// 2 element integer vector.
using Vec2i = glm::ivec2;

} // namespace Folk


#endif // FOLK_UTILS__VECTOR_HPP