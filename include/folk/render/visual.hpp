#ifndef FOLK_RENDER__VISUAL_HPP
#define FOLK_RENDER__VISUAL_HPP

#include "folk/core/resource.hpp"
#include "folk/render/material.hpp"
#include "folk/render/mesh.hpp"

namespace Folk
{

/// \~spanish Recurso que agrupa una malla y un material. \~english A resource that pairs a Mesh and a Material.
/**
 * \see Mesh
 * \see Material
 * \see Resource
*/
class Visual : public Resource {
    
public:
    using Ref = Reference<Visual>;

    /// \brief \~spanish Crea un nuevo objeto a partir de una malla y un material.
    /// \brief \~english Instance a new visual from the given mesh and material.
    static Ref create(Mesh::Ref, Material::Ref);

    /// \brief \~spanish Configura la malla a utilizar.
    /// \brief \~english Change the mesh.
    void setMesh(Mesh::Ref);

    /// \~spanish Obtiene una referencia a la malla en uso.
    /// \~english Retrieve a \ref Reference to this visual's mesh.
    Mesh::Ref getMesh() const;

    /// \~spanish Cambia el material.
    /// \~english Change material.
    void setMaterial(Material::Ref);

    /// \~spanish Obtiene una referencia al material en uso.
    /// \~english Retrieve a \ref Reference to this Visual's material.
    Material::Ref getMaterial() const;

private:
    Mesh::Ref mesh;
    Material::Ref material;

    Visual(Mesh::Ref, Material::Ref);

    Visual(Visual const&) = delete;
    Visual& operator=(Visual const&) = delete;

    friend class Renderer;
};

} // namespace folk


#endif // FOLK_RENDER__VISUAL_HPP