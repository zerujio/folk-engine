#ifndef FOLK_MATH__MATRIX_HPP
#define FOLK_MATH__MATRIX_HPP

#include <iostream>
#include <cstdint>

namespace Folk
{

class Matrix4f {
public:
    float* operator[](const std::size_t k) {
        return m_array[k];
    }

    const float* operator[](const std::size_t k) const {
        return m_array[k];
    }

    operator const float*() const {
        return m_array[0];
    }

    operator float*() {
        return m_array[0];
    }

private:
    float m_array[4][4];
};

std::ostream& operator<<(std::ostream& out, const Matrix4f& mat); 

} // namespace Folk

#endif // FOLK_MATH__MATRIX_HPP