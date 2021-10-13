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
    using MeshRef = Reference<Mesh>;
    using MaterialRef = Reference<Material>;

    static Ref create(MeshRef, MaterialRef);

    void setMesh(MeshRef const&);
    MeshRef getMesh();

    void setMaterial(MaterialRef const&);
    MaterialRef getMaterial();

    ~Visual();

private:
    MeshRef mesh;
    MaterialRef material;
    GLuint vao;

    Visual(MeshRef, MaterialRef);
    Visual(Visual const&);
    Visual& operator=(Visual const&);

    void bindBuffers();
    void enableVertexAttributes();

    friend class RenderModule;
};

} // namespace folk


#endif // FOLK_RENDER__VISUAL_HPP