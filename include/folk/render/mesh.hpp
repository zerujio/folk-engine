#ifndef FOLK_RENDER__MESH_HPP
#define FOLK_RENDER__MESH_HPP

#include "folk/core/resource.hpp"
#include "folk/render/immediate_geometry.hpp"

namespace Folk
{

namespace ImplDetails {
struct MeshData;
}

/// \~spanish Recurso que representa una malla 3D. \~english Resource to keep track of a 3D mesh.
class Mesh : public Resource {
public:
    /// Crea una malla vacía. !!! ELIMINAR ESTE CONSTRUCTOR. Eliminar emptyIB, emptyVB
    static std::shared_ptr<Mesh> create();

    /// Crea una malla a partir de geometría inmediata.
    /**
     * \see ImmediateGeometry
    */
   static std::shared_ptr<Mesh> create(ImmediateGeometry const&);

protected:
    Mesh() = default;
};
    
} // namespace folk

#endif // FOLK_RENDER__MESH_HPP