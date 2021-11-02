#ifndef FOLK_UTILS__VECTOR_HPP
#define FOLK_UTILS__VECTOR_HPP

#include <array>
#include <cstddef>

namespace Folk
{

/// Un vector de N elementos de tipo T.
template<int N, typename T>
class Vector {
protected:
    std::array<T, N> arr;

public:
    /// Accede a una componente del vector.
    /**
     * Accder a un índice mayor o igual a la dimensión del vector es comportamiento
     * indefinido.
     * 
     * \param k índice de la componente.
     * \return una referencia a la componente.
     */
    constexpr T& operator[](std::size_t k) {
        return arr[k];
    }
};

template<typename T = double>
class Vector3 : Vector<3, T> {
public:
    T& x = this->arr[0];
    T& y = this->arr[1];
    T& z = this->arr[2];
};

template<typename T = double>
class Vector2 : Vector<2, T> {
public:
    T& x = this->arr[0];
    T& y = this->arr[1];
};

using vec2 = Vector2<float>;
using dvec2 = Vector2<double>;
using vec3 = Vector3<float>;
using dvec3 = Vector3<double>;

} // namespace Folk


#endif // FOLK_UTILS__VECTOR_HPP