//
// Created by sergio on 05-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__VERTEX_ARRAY_HPP
#define INCLUDE_FOLK_RENDER__VERTEX_ARRAY_HPP

#include "gl_buffer.hpp"
#include "gl_vertex_array.hpp"
#include "folk/math/vector.hpp"

#include <array>

namespace Folk {

/// Specifies a vertex attribute.
struct VertexAttribute {
    enum class Type {
        Int = GL_INT,
        UInt = GL_UNSIGNED_INT,
        Float = GL_FLOAT,
        Double = GL_DOUBLE
    };
    enum class Size { X = 1, XY, XYZ, XYZW };

    Type type;  /// data type
    Size size;  /// number of values
    bool norm; /// Should values be normalized (clamped)?

    /// Size in bytes.
    [[nodiscard]]
    constexpr GLsizei rawSize() const {
        GLsizei s {0};

        switch (type) {
            case Type::Int:
                s = sizeof(int);
                break;

            case Type::UInt:
                s = sizeof(unsigned int);
                break;

            case Type::Float:
                s = sizeof(float);
                break;

            case Type::Double:
                s = sizeof(double);
                break;
        }

        return s * static_cast<GLsizei>(size);
    }
};

template<class Type> struct GetVectorAttributes;
template<class T, auto N, auto P>
struct GetVectorAttributes<glm::vec<N, T, P>> {
    using type = T;
    static constexpr auto size = N;
};

template<class T> auto getVertexAttributeType();
template<> auto getVertexAttributeType<GLint>() { return VertexAttribute::Type::Int; }
template<> auto getVertexAttributeType<GLuint>() { return VertexAttribute::Type::UInt; }
template<> auto getVertexAttributeType<GLfloat>() { return VertexAttribute::Type::Float; }
template<> auto getVertexAttributeType<GLdouble>() { return VertexAttribute::Type::Double; }

/**
 * @brief Construct a VertexAttribute specification for a vector type (Vec3, Vec2i, etc...).
 * @tparam T A vector type.
 * @param normalize Should the values be clamped?
 * @return A VertexAttribute object.
 */
template<class T>
VertexAttribute makeAttrib(bool normalize) {

    using attribs = GetVectorAttributes<T>;

    return {getVertexAttributeType<typename attribs::type>(),
            static_cast<VertexAttribute::Size>(attribs::size),
            normalize};
}

/**
 * @brief A vertex array in GPU memory.
 */
class VertexArray {

public:
    /**
     * @brief Initialize the array from a container.
     * @tparam Container A contiguous memory container such as std::vector or std::array.
     * @tparam NAttr Number of vertex attributes
     * @param data
     */
    template<class Container, int NAttr>
    VertexArray(const Container& data, std::array<VertexAttribute, NAttr> attributes)
    {
        m_vao.bind();
        m_buffer.bind(gl::BufferTarget::Array);

        writeBuffer(sizeof(Container::value_type) * data.size(), data.data());

        GLsizei stride {0};
        for (const VertexAttribute& att : attributes) {
            stride += att.rawSize();
        }

        int i {0};
        GLsizei offset {0};
        for (const VertexAttribute& attrib : attributes) {
            addVertexAttribute(i++, attrib, stride, offset);
            offset += attrib.rawSize();
        }

        gl::VertexArrayHandle::unbind();
    }

    void bind() const;

    static void unbind();

private:
    gl::BufferManager m_buffer {};
    gl::VertexArrayManager m_vao {};

    /**
     * @brief Write vertex data to currently bound vertex array buffer.
     * @param data An opaque pointer to data.
     * @param size Size in bytes of the data.
     */
    static void writeBuffer(const void* data, GLsizei size) ;

    /**
     * @brief Add a vertex attribute to currently bound VAO.
     * @param index index (location) of the attribute.
     * @param attribute A vertex attribute specification.
     * @param stride Separation between consecutive attributes (i.e. size of the whole vertex).
     * @param offset Distance from the start of the buffer to the first instance of the attribute (or from the start of
     * vertex to the attribute).
     */
    static void addVertexAttribute(int index, const VertexAttribute& attribute, GLsizei stride, GLsizei offset) ;
};

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__VERTEX_ARRAY_HPP
