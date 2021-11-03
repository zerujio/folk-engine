#include "folk/render/visual.hpp"
#include "../core/engine_singleton.hpp"
#include "renderer.hpp"

namespace Folk
{

Visual::Visual(Mesh::Ref mesh_, Material::Ref mat_) 
    : mesh(mesh_), material(mat_)
{}

Visual::Ref Visual::create(Mesh::Ref mesh_, Material::Ref mat_) {
    return {new Visual(mesh_, mat_)};
}

void Visual::setMesh(Mesh::Ref mesh_) {
    mesh = mesh_;
}

Mesh::Ref Visual::getMesh() const {
    return mesh;
}

void Visual::setMaterial(Material::Ref material_) {
    material = material_;
}

Material::Ref Visual::getMaterial() const {
    return material;
}

} // namespace folk
