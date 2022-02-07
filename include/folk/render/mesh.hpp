#ifndef FOLK_RENDER__MESH_HPP
#define FOLK_RENDER__MESH_HPP

#include "folk/core/resource.hpp"
#include "immediate_geometry.hpp"
#include "vertex_array.hpp"

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
    Mesh(const V& vertices, const I& indices, const DrawMode mode) :
            m_vertex_array(vertices, indices),
            m_draw_mode(mode)
    {}

    /// Crea una malla a partir de geometría inmediata.
    /**
     * \see ImmediateGeometry
     */
    template<class Vertex = PositionColorVertex, class Index = GLushort>
    static std::shared_ptr<Mesh> create(ImmediateGeometry<Vertex, Index> const& geometry,
                                        DrawMode mode = DrawMode::Triangles)
    {
        return std::make_shared<Mesh>( geometry.vertices, geometry.indices, mode );
    }

    /// Create a cube.
    static std::shared_ptr<Mesh> createCube(Color color);

    [[nodiscard]] DrawMode getDrawMode() const;

    void setDrawMode(DrawMode draw_mode);

private:
    VertexArray m_vertex_array;
    DrawMode m_draw_mode;
};
    
} // namespace folk

#endif // FOLK_RENDER__MESH_HPP