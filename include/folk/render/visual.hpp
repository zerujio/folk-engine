#ifndef FOLK_RENDER__VISUAL_HPP
#define FOLK_RENDER__VISUAL_HPP

#include "folk/core/resource.hpp"
#include "folk/render/material.hpp"
#include "folk/render/mesh.hpp"

namespace Folk
{

/// A resource that pairs a Mesh and a Material.
/**
 * @see Mesh
 * @see Material
 * @see Resource
*/
class Visual : public Resource {
    
public:
    using Ref = Reference<Visual>;

    /// Instance a new visual from the given mesh and material.
    static Ref create(Mesh::Ref, Material::Ref);

    /// Change the mesh.
    void setMesh(Mesh::Ref);

    /// Retrieve a @ref Reference to this visual's mesh.
    Mesh::Ref getMesh() const;

    /// Change material.
    void setMaterial(Material::Ref);

    /// Retrieve a @ref Reference to this Visual's material.
    Material::Ref getMaterial() const;

    ~Visual();

private:
    Mesh::Ref mesh;
    Material::Ref material;

    Visual(Mesh::Ref, Material::Ref);

    Visual(Visual const&);
    Visual& operator=(Visual const&);

    Visual(Visual&&);
    Visual& operator=(Visual&&);

    void bindBuffers();
    void enableVertexAttributes();

    friend class RenderModule;
};

} // namespace folk


#endif // FOLK_RENDER__VISUAL_HPP