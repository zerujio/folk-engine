#ifndef FOLK_RENDER__MESH_HPP
#define FOLK_RENDER__MESH_HPP

#include "folk/core/resource.hpp"
#include "folk/render/immediate_geometry.hpp"

#include <bgfx/bgfx.h>

namespace Folk
{

/// \~spanish Recurso que representa una malla 3D. \~english Resource to keep track of a 3D mesh.
class Mesh final : public Resource {
public:
    /// Constructor de uso interno.
    Mesh(const bgfx::VertexBufferHandle, const bgfx::IndexBufferHandle);

    ~Mesh();

    /// Crea una malla a partir de geometría inmediata.
    /**
     * \see ImmediateGeometry
    */
   static std::shared_ptr<Mesh> create(ImmediateGeometry const&);

private:
    const bgfx::VertexBufferHandle vb;
    const bgfx::IndexBufferHandle ib;

    friend class Renderer;
};
    
} // namespace folk

#endif // FOLK_RENDER__MESH_HPP