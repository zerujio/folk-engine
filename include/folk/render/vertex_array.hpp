//
// Created by sergio on 05-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__VERTEX_ARRAY_HPP
#define INCLUDE_FOLK_RENDER__VERTEX_ARRAY_HPP

#include "gl_buffer.hpp"
#include "gl_vertex_array.hpp"
#include "folk/math/vector.hpp"
#include "vertex_attribute.hpp"
#include "vertex_types.hpp"
#include "index_types.hpp"
#include "draw_mode.hpp"

#include <array>
#include <cinttypes>
#include <cstddef>

namespace Folk {

/**
 * @brief A vertex array in GPU memory.
 */
class VertexArray {

    friend class Renderer;

public:
    /**
     * @brief Initialize the array from a container.
     * @tparam VertexContainer A contiguous memory container such as std::vector or std::array. The value type should be
     * a Vertex struct.
     * @tparam IndexContainer A contiguous memory container such as std::vector or std::array. The value type should be
     * either GLuint or GLushort.
     * @param vertex_data An array of vertices.
     * @param index_data An array of indices. Every three indices a triangle is defined.
     *
     * A Vertex struct is a POD type that defines a static member that specifies its VertexAttributes. See PositionVertex
     * and PositionColorVertex for an example.
     */
    template<class VertexContainer, class IndexContainer>
    VertexArray(const VertexContainer& vertex_data, const IndexContainer& index_data) :
        m_index_count(index_data.size()),
        m_index_type(getIndexTypeOf<typename IndexContainer::value_type>())
    {
        m_vao.bind();

        bufferData(vertex_data.data(), sizeof(typename VertexContainer::value_type) * vertex_data.size(),
                   m_vertex_buffer, gl::BufferTarget::Array);

        bufferData(index_data.data(), sizeof(typename IndexContainer::value_type) * index_data.size(),
                   m_index_buffer, gl::BufferTarget::ElementArray);

        const auto stride {sizeof(typename VertexContainer::value_type)};
        const auto& attributes = VertexContainer::value_type::vertex_attributes;

        int i {0};
        for (const VertexAttribute& attrib : attributes) {
            addVertexAttribute(i++, attrib, stride);
        }

        gl::VertexArrayHandle::unbind();
        gl::BufferHandle::unbind(gl::BufferTarget::Array);
        gl::BufferHandle::unbind(gl::BufferTarget::ElementArray);
    }

    /// Bind this array's VAO
    void bind() const;

    /// Unbind the currently bound VAO
    static void unbind();

private:
    IndexType m_index_type;
    std::size_t m_index_count;
    gl::BufferManager m_index_buffer {};
    gl::BufferManager m_vertex_buffer {};
    gl::VertexArrayManager m_vao {};

    // bind and write data to a buffer.
    static void bufferData(const void* data, GLsizei size, gl::BufferHandle buffer, gl::BufferTarget target);

    // Add a vertex attribute to currently bound VAO.
    static void addVertexAttribute(int index, const VertexAttribute& attribute, GLsizei stride);
};

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__VERTEX_ARRAY_HPP
