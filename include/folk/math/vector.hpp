#ifndef FOLK_UTILS__VECTOR_HPP
#define FOLK_UTILS__VECTOR_HPP

#include "bx/math.h"

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


static constexpr float add(const float x, const float y) { return x + y; }

static constexpr float sub(const float x, const float y) { return x - y; }

static constexpr float mul(const float x, const float y) { return x * y; }

static constexpr float div(const float x, const float y) { return x / y; }

struct Vec3 final {
    float x {0.0f};
    float y {0.0f};
    float z {0.0f};

    constexpr Vec3() = default;
    constexpr Vec3(const float x_, const float y_, const float z_) noexcept : x(x_), y(y_), z(z_) {}
    constexpr Vec3(const bx::Vec3 v) noexcept : x(v.x), y(v.y), z(v.z) {}

    template<float (*F)(float, float)>
    Vec3& map(const float k) {
        x = F(x, k);
        y = F(y, k);
        z = F(z, k);

        return *this;
    }

    template<float (*F)(float, float)>
    Vec3& map(const Vec3& other) {
        x = F(x, other.x);
        y = F(y, other.y);
        z = F(z, other.z);
        return *this;
    }

    Vec3& operator+=(const Vec3& other) {
        return map<add>(other);
    }

    Vec3& operator-=(const Vec3& other) {
        return map<sub>(other);
    }

    Vec3& operator*=(const float k) {
        return map<mul>(k);
    }

    Vec3& operator/=(const float k) {
        return map<div>(k);
    }

    explicit constexpr operator bx::Vec3() const {
        return {x, y, z};
    }

    operator const float*() const {
        return reinterpret_cast<const float*>(this);
    }

    operator float*() {
        return reinterpret_cast<float *>(this);
    }

    [[nodiscard]] Vec3 normalized() const {
        return Vec3(bx::normalize(bx::Vec3(*this)));
    }

    [[nodiscard]] float length() const {
        return bx::length(bx::Vec3(*this));
    }

    [[nodiscard]] constexpr float lengthSquared() const {
        return x*x + y*y + z*z;
    }
};

constexpr Vec3 operator-(const Vec3 v) {
    return {-v.x, -v.y, -v.z};
}

template<float (*F)(float, float)>
constexpr Vec3 map(const Vec3 v, const float k) {
    return {F(v.x, k), F(v.y, k), F(v.z, k)};
}

constexpr Vec3 operator*(const Vec3 v, const float k) {
    return map<mul>(v, k);
}

constexpr Vec3 operator/(const Vec3 v, const float k) {
    return map<div>(v, k);
}

template<float (*F)(float, float)>
constexpr Vec3 map(const Vec3 l, const Vec3 r){
    return {F(l.x, r.x), F(l.y, r.y), F(l.z, r.z)};
}

constexpr Vec3 operator+(const Vec3 l, const Vec3 r) {
    return map<add>(l, r);
}

constexpr Vec3 operator-(const Vec3 l, const Vec3 r) {
    return map<sub>(l, r);
}

constexpr bool operator==(const Vec3 l, const Vec3 r) {
    return (l.x == r.x ) and (l.y == r.y) and (l.z == r.z);
}

constexpr bool operator!=(const Vec3 l, const Vec3 r) {
    return (l.x != r.x) or (l.y != r.y) or (l.z != r.z);
}

inline std::ostream& operator<<(std::ostream &out, const Vec3& vec) {
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}
} // namespace Folk


#endif // FOLK_UTILS__VECTOR_HPP