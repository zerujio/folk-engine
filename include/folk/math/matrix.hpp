#ifndef FOLK_MATH__MATRIX_HPP
#define FOLK_MATH__MATRIX_HPP

#include "glm/mat4x4.hpp"

#include <iostream>

namespace Folk
{

/// 4 by 4 floating point matrix.
using Mat4 = glm::mat4;

std::ostream& operator<<(std::ostream& out, const Mat4& mat);

} // namespace Folk

#endif // FOLK_MATH__MATRIX_HPP