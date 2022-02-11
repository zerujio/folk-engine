//
// Created by sergio on 06-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__VERTEX_ATTRIBUTE_HPP
#define INCLUDE_FOLK_RENDER__VERTEX_ATTRIBUTE_HPP

#include "gl.hpp"
#include "folk/math/vector.hpp"

namespace Folk {

/// Specifies a vertex attribute (data type of vertices in a vertex buffer).
struct VertexAttribute {

    /// Data type
    struct TypeInfo {

        enum class Enum {
            Byte = GL_BYTE,
            UByte = GL_UNSIGNED_BYTE,
            Short = GL_SHORT,
            UShort = GL_UNSIGNED_SHORT,
            Int = GL_INT,
            UInt = GL_UNSIGNED_INT,
            Float = GL_FLOAT,
            Double = GL_DOUBLE,
        };

        Enum gl_enum;
        GLsizei size;
    };
    TypeInfo type;

    /// Size (number of elements)
    enum class Count {
        X = 1, XY = 2, XYZ = 3, XYZW = 4,
        R = 1, RG = 2, RGB = 3, RGBA = 4,
        S = 1, ST = 2, STP = 3, STPQ = 4
    };
    Count count;

    /**
     * @brief Are values normalized?
     * If true, integers are linearly mapped to floating point values in the range [-1, 1] for signed types, and [0, 1]
     * for unsigned types.
     */
    bool normalize;

    /**
     * @brief Location used in the GLSL shader to match the vertex data to an attribute.
     * The first few indices are used for some common attributes: position, normals, texture coordinates. To avoid
     * conflicts with these when using user-defined attributes it is recommended to prefix the location with a 1.
     * That is, for example, instead of using location 2, use location 12.
     */
    GLuint location;
    struct Location { enum : GLuint {Position, Normal, TexCoord}; };

private:
    template<typename T> struct TypeInfoOf_struct;

    template<class> struct vector_struct;
    template<auto L, typename T, auto P>
    struct vector_struct<glm::vec<L, T, P>> {
        using type = T;
        static constexpr Count length = static_cast<Count>(L);
    };

public:
    template<typename T> static constexpr TypeInfo type_info_of { TypeInfoOf_struct<T>::value };

    template<class V>
    static constexpr VertexAttribute fromVectorType(const bool normalize_, const GLuint location_) noexcept {
        return {type_info_of<typename vector_struct<V>::type>, vector_struct<V>::length, normalize_, location_};
    }
};

#define FOLK_TYPE_INFO_OF_DEF(TYPE, ENUM)\
template<> struct VertexAttribute::TypeInfoOf_struct<TYPE> { static constexpr TypeInfo value {TypeInfo::Enum::ENUM, sizeof(TYPE)}; };
FOLK_TYPE_INFO_OF_DEF(GLbyte, Byte)
FOLK_TYPE_INFO_OF_DEF(GLubyte, UByte)
FOLK_TYPE_INFO_OF_DEF(GLshort, Short)
FOLK_TYPE_INFO_OF_DEF(GLushort, UShort)
FOLK_TYPE_INFO_OF_DEF(GLint, Int)
FOLK_TYPE_INFO_OF_DEF(GLuint, UInt)
FOLK_TYPE_INFO_OF_DEF(GLfloat, Float)
FOLK_TYPE_INFO_OF_DEF(GLdouble, Double)

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__VERTEX_ATTRIBUTE_HPP
