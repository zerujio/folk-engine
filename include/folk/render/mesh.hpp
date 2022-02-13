#ifndef FOLK_RENDER__MESH_HPP
#define FOLK_RENDER__MESH_HPP

#include "folk/core/resource.hpp"
#include "immediate_geometry.hpp"
#include "vertex_types.hpp"
#include "gl_buffer.hpp"
#include "gl_vertex_array.hpp"
#include "index_types.hpp"

namespace Folk
{

/// \~spanish Recurso que representa una malla 3D. \~english Resource to keep track of a 3D mesh.
class Mesh final : public Resource {

    friend class Renderer;

public:
    /**
     * @brief Construct a Mesh (i.e. load into GPU memory). Do not use directly, use the create* static methods instead.
     * @tparam V A container type for vertices.
     * @tparam I A container type for indices.
     * @param vertices Vertex data.
     * @param indices Index data.
     * @param mode Draw mode (triangles, lines, etc.).
     */
    template<class V, class I>
    Mesh(const V& vertices, const I& indices)
    : m_index_type(getIndexTypeOf<typename I::value_type>()), m_index_count(indices.size())
    {
        using vertex_t = typename V::value_type;
        using index_t = typename I::value_type;

        m_vertex_buffer.bind(gl::BufferTarget::Array);
        gl::Buffer::data(gl::BufferTarget::Array,
                         sizeof(vertex_t) * vertices.size(),
                         vertices.data(),
                         gl::BufferUsage::StaticDraw);

        m_vertex_array.bind();

        m_index_buffer.bind(gl::BufferTarget::ElementArray);
        gl::Buffer::data(gl::BufferTarget::ElementArray,
                         sizeof(index_t) * indices.size(),
                         indices.data(),
                         gl::BufferUsage::StaticDraw);

        for (const VertexAttribSpec& spec : V::value_type::vertex_attributes)
            configureVertexAttribute(spec.index, spec.attribute, sizeof(vertex_t), spec.offset);

        gl::VertexArray::unbind();
        gl::Buffer::unbind(gl::BufferTarget::Array);
        gl::Buffer::unbind(gl::BufferTarget::ElementArray);
    }

    /// Crea una malla a partir de geometría inmediata.
    /**
     * \see ImmediateGeometry
     */
    template<class Vertex = PositionNormalVertex, class Index = GLushort>
    static std::shared_ptr<Mesh> create(ImmediateGeometry<Vertex, Index> const& geometry)
    {
        return std::make_shared<Mesh>( geometry.vertices, geometry.indices);
    }

    /// Create a cube.
    static std::shared_ptr<Mesh> createCube();

private:
    IndexType m_index_type;
    GLsizei m_index_count;
    gl::BufferManager m_index_buffer {};
    gl::BufferManager m_vertex_buffer {};
    gl::VertexArrayManager m_vertex_array {};

    static void configureVertexAttribute(GLuint index, const VertexAttribute &attribute, GLsizei stride, GLuint offset);
};
    
} // namespace folk

#endif // FOLK_RENDER__MESH_HPP