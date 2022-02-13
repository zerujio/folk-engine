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
    static constexpr VertexAttribute fromVectorType(const bool normalize_) noexcept {
        return {type_info_of<typename vector_struct<V>::type>, vector_struct<V>::length, normalize_};
    }
};

/// Default indices for vertex attributes.
enum class DefaultAttribIndex {
    Position,
    Normal,
    TexCoord,
    Color
};

/**
 * @brief Specifies all the necessary data to link a vertex buffer's data to a vertex shader input variable.
 *
 * All Vertex types must define a constant static data member named @p vertex_attributes of type
 * `std::array<VertexAttributeSpec, N>`. This is required for the engine to be able to match the vertex data with the
 * corresponding shader variable.
 */
struct VertexAttribSpec final {

    VertexAttribSpec() = default;

    constexpr VertexAttribSpec(GLuint index_, const VertexAttribute& attribute_, GLuint offset_) noexcept
    : index(index_), attribute(attribute_), offset(offset_)
    {}

    constexpr VertexAttribSpec(DefaultAttribIndex index_, const VertexAttribute& attribute_, GLuint offset_) noexcept
    : index(static_cast<GLuint>(index_)), attribute(attribute_), offset(offset_)
    {}

    /**
     * @brief The attribute index used to match vertex data with shader variables.
     *
     * All active (not unused) GLSL variables will be assigned an index when program linking happens. Variables declared
     * `in type variable_name` take their values from vertex attributes. That is, if the vertex shader declares the
     * following variable:
     *
     *     in vec3 a_position;
     *
     * and V is a vertex struct defined as:
     *
     *      struct V {
     *          Vec3 position;
     *          Vec3 normal;
     *      };
     *
     * then the attribute specification for @p position should have its @p index set to @ a_position 's index. The
     * result will be that when a Mesh whose vertex data has type @p V is drawn, within the vertex shader the variable
     * @p a_position will take the value of the field @p position of the corresponding vertex.
     *
     *  ---
     *
     * The index of a variable is determined in two ways:
     *
     * - In the static member variables Shader::attribute_indices and Shader::builtin_attribute_indices. These are lists
     * of variable names and the indices to be assigned to each one.
     * - By explicitly specifying it in the vertex shader through the `layout(location = i) in type variable_name`
     * syntax, where @p i is a positive integer literal that will determine the index of the variable in the linked
     * program.
     *
     * Note that the second method always takes precedence.
     */
    GLuint index;

    /// Attribute type information. @see VertexAttribute
    VertexAttribute attribute;

    /**
     * @brief The byte offset from the start of the buffer to the first instance of the attribute.
     *
     * Vertex types have interleaved attributes, so for a vertex struct defined as:
     *
     *      struct V {
     *          Vec3 pos;
     *          Vec3 norm;
     *      };
     *
     * the @p offset of @p pos would be 0, and the one of @p norm would be `sizeof(Vec3)` (or `offsetof(V, norm)`).
     */
    GLuint offset;
};

// definitions
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
