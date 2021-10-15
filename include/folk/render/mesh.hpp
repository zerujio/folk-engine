#ifndef FOLK_RENDER__MESH_HPP
#define FOLK_RENDER__MESH_HPP


#include "folk/core/resource.hpp"
#include "folk/render/immediate_geometry.hpp"
#include "folk/render/common.hpp"

namespace Folk
{

/// @ref Resource to keep track of a 3D mesh.
class Mesh : public Resource {
public:
    using Ref = Reference<Mesh>;

    /// Create empty mesh.
    /**
     * @return a reference to the newly instanced mesh.
    */
    static Ref createEmpty();

    /// Create Mesh from @ref ImmediateGeometry .
    /**
     * @param geometry immediate geometry.
     * @return a reference to the newly instanced mesh.
    */
    static Ref create(ImmediateGeometry const& geometry);

    ~Mesh();

private:
    Mesh(VertexArray const&, IndexArray const&);
    Mesh(Mesh const&);
    Mesh(Mesh&&);
    Mesh& operator=(Mesh const&);
    Mesh& operator=(Mesh&&);

    friend class RenderModule;
    friend class Visual;
};
    
} // namespace folk

#endif // FOLK_RENDER__MESH_HPP