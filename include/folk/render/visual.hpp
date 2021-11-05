#ifndef FOLK_RENDER__VISUAL_HPP
#define FOLK_RENDER__VISUAL_HPP

#include "folk/core/resource.hpp"
#include "folk/render/material.hpp"
#include "folk/render/mesh.hpp"

namespace Folk
{

namespace ImplDetails {
struct VisualData;
}

/// \~spanish Recurso que agrupa una malla y un material. \~english A resource that pairs a Mesh and a Material.
/**
 * \see Mesh
 * \see Material
 * \see Resource
*/
class Visual : public Resource {
    
public:
    /// Crea una Visual con material predeterminado y geometría vacía.
    static std::shared_ptr<Visual> create(); 

    /// Crea una Visual con material predeterminado y la malla provista.
    static std::shared_ptr<Visual> create(std::shared_ptr<Mesh>);

    /// Crea una Visual con el material provisto y geometría vacía.
    static std::shared_ptr<Visual> create(std::shared_ptr<Material>);

    /// Crea una Visual con el Material y Mesh provistos.
    static std::shared_ptr<Visual> create(std::shared_ptr<Mesh>, std::shared_ptr<Material>);

    /// Cambia la malla
    void setMesh(std::shared_ptr<Mesh> mesh);

    /// Obtiene la malla
    std::shared_ptr<Mesh> getMesh();

    /// Asigna el material
    void setMaterial(std::shared_ptr<Material> material);

    /// Obtiene el material
    std::shared_ptr<Material> getMaterial();

protected:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;

    Visual(std::weak_ptr<Mesh> mesh_, std::weak_ptr<Material> material_)
        :  mesh(mesh_), material(material_)
    {}

    ~Visual() {}
};

} // namespace folk


#endif // FOLK_RENDER__VISUAL_HPP