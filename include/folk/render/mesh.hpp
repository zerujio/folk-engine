#ifndef FOLK_RENDER__MESH_HPP
#define FOLK_RENDER__MESH_HPP

#include "folk/core/resource.hpp"
#include "folk/render/immediate_geometry.hpp"

namespace Folk
{

/// \~spanish Recurso que representa una malla 3D. \~english Resource to keep track of a 3D mesh.
class Mesh : public Resource {
public:
    using Ref = Reference<Mesh>;

    /// \~spanish Crea una malla vacía. \~english Create empty mesh.
    static Ref createEmpty();

    /// \~spanish Crea una malla a partir de ImmediateGeometry \~english Create Mesh from \ref ImmediateGeometry .
    static Ref create(ImmediateGeometry const& geometry);

    ~Mesh();

private:
    Mesh(ImmediateGeometry::VertexArray const&, 
         ImmediateGeometry::IndexArray const&);
    Mesh(Mesh const&) = delete;
    Mesh& operator=(Mesh const&) = delete;

    friend class Renderer;
    friend class Visual;
};
    
} // namespace folk

#endif // FOLK_RENDER__MESH_HPP