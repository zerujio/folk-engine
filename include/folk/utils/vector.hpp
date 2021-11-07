#ifndef FOLK_UTILS__VECTOR_HPP
#define FOLK_UTILS__VECTOR_HPP

#include <array>
#include <iostream>

namespace Folk
{

template<class T>
class Vector2 {
public:
    T x;
    T y;
};

using Vec2d = Vector2<double>;
using Vec2f = Vector2<float>;
using Vec2i = Vector2<int>;

template<class T>
class Vector3 {
public:
    T x; 
    T y;
    T z;

    template<T (*F)(T)>
    Vector3 map() const {
        return {F(x), F(y), F(z)};
    }

    template<T (*F)(T, T)>
    Vector3 map(const T k) const {
        return {F(x, k), F(y, k), F(z, k)}; 
    }

    Vector3 operator-() const {
        return map<minus>();
    }

    Vector3 operator*(T k) const {
        return map<mul>(k);
    }

    operator T*() {
        return &x;
    }

    operator const T*() const {
        return &x;
    }

private:
    static T minus(T x) {
        return -x;
    }

    static T mul(T x, T y) {
        return x, y;
    }
};

template<class T>
std::ostream& operator<<(std::ostream &out, const Vector3<T>& vec) {
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

using Vec3f = Vector3<float>;
using Vec3i = Vector3<int>;

template<class T, T(*F)(T, T)>
Vector3<T> map(const Vector3<T>& l, const Vector3<T>& r) {
    return {F(l.x, l.y), F(l.y, r.y), F(l.z, r.z)};
}

template<class T>
inline bool operator==(Vector3<T> const& l, Vector3<T> const& r) {
    return (l.x == r.x) and (l.y == r.y) and (l.z == r.z);
}

template<class T>
inline bool operator!=(const Vector3<T>& l, const Vector3<T>& r) {
    return !(l == r);
}

} // namespace Folk


#endif // FOLK_UTILS__VECTOR_HPP