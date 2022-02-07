//
// Created by sergio on 06-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__VERTEX_ATTRIBUTE_HPP
#define INCLUDE_FOLK_RENDER__VERTEX_ATTRIBUTE_HPP

#include "gl.hpp"

namespace Folk {

enum class VertexAttributeType {
    Byte = GL_BYTE,
    UByte = GL_UNSIGNED_BYTE,
    Int = GL_INT,
    UInt = GL_UNSIGNED_INT,
    Float = GL_FLOAT,
    Double = GL_DOUBLE,
};

constexpr auto getAttributeSize(VertexAttributeType type) {
    switch (type) {
        case VertexAttributeType::Byte:
        case VertexAttributeType::UByte:
            return sizeof(GLbyte);

        case VertexAttributeType::Int:
        case VertexAttributeType::UInt:
            return sizeof(GLint);

        case VertexAttributeType::Float:
             return sizeof(GLfloat);

        case VertexAttributeType::Double:
            return sizeof(GLdouble);
    }
}

enum class VertexAttributeSize { X = 1, XY, XYZ, XYZW };

/// Specifies a vertex attribute.
struct VertexAttribute {

    /// data type
    VertexAttributeType type;

    /// number of values
    VertexAttributeSize size;

    /// Are values normalized? (true = integers turn into fixed point decimal values in the range [-1, 1] (or [0, 1] for unsigned)).
    bool normalize;

    /// Offset of the attribute (i.e. offset_of)
    GLuint offset;

    /// Size in bytes.
    [[nodiscard]]
    constexpr GLsizei rawSize() const {
        GLsizei s {0};

        return s * static_cast<GLsizei>(size);
    }
};

template<class T> constexpr auto getVertexAttributeType();
template<> constexpr auto getVertexAttributeType<GLint>() { return VertexAttributeType::Int; }
template<> constexpr auto getVertexAttributeType<GLuint>() { return VertexAttributeType::UInt; }
template<> constexpr auto getVertexAttributeType<GLfloat>() { return VertexAttributeType::Float; }
template<> constexpr auto getVertexAttributeType<GLdouble>() { return VertexAttributeType::Double; }

template<int N> constexpr auto getVertexAttributeSize();
template<> constexpr auto getVertexAttributeSize<1>() { return VertexAttributeSize::X; }
template<> constexpr auto getVertexAttributeSize<2>() { return VertexAttributeSize::XY; }
template<> constexpr auto getVertexAttributeSize<3>() { return VertexAttributeSize::XYZ; }
template<> constexpr auto getVertexAttributeSize<4>() { return VertexAttributeSize::XYZW; }

template<class Type> struct VectorAttributes;
template<class T, auto N, auto P>
struct VectorAttributes<glm::vec<N, T, P>> {
    static constexpr VertexAttributeType type {getVertexAttributeType<T>()};
    static constexpr VertexAttributeSize size {getVertexAttributeSize<N>()};
};

/**
 * @brief Construct a VertexAttribute specification for a vector type (Vec3, Vec2i, etc...).
 * @tparam T A vector type.
 * @param normalize Should the values be clamped?
 * @return A VertexAttribute object.
 */
template<class T>
constexpr VertexAttribute makeVertexAttribute(bool normalize, unsigned int offset) noexcept {
    using Attributes = VectorAttributes<T>;
    return {Attributes::type, Attributes::size, normalize, offset};
}

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__VERTEX_ATTRIBUTE_HPP
