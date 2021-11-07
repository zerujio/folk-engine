#include "folk/math/matrix.hpp"

namespace Folk
{

std::ostream& operator<<(std::ostream& out, const Matrix4f& mat) {
    const float* p = mat;

    out << "[ [" << p[0] << ", " << p[1] << ", " << p[2] << ", " << p[3] << "], "
        << "[" << p[4] << ", " << p[5] << ", " << p[6] << ", " << p[7] << "], "
        << "[" << p[8] << ", " << p[9] << ", " << p[10] << ", " << p[11] << "], "
        << "[" << p[12] << ", " << p[13] << ", " << p[14] << ", " << p[15] << "] ]";
    
    return out;
}

} // namespace Folk
