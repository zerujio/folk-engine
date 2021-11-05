#include "folk/render/visual.hpp"

#include "../core/engine_singleton.hpp"

#include "visual_data.hpp"
#include "renderer.hpp"

namespace Folk
{

std::shared_ptr<Visual> Visual::create() {
    return create(Mesh::create(), Material::create());
}

std::shared_ptr<Visual> Visual::create(std::shared_ptr<Mesh> mesh_) {
    return create(mesh_, Material::create());
}

std::shared_ptr<Visual> Visual::create(std::shared_ptr<Material> material_) {
    return create(Mesh::create(), material_);
}

std::shared_ptr<Visual> Visual::create(std::shared_ptr<Mesh> mesh_,
                                       std::shared_ptr<Material> material_)
{
    auto data_ptr = std::make_shared<VisualData>(mesh_, material_);
    return std::shared_ptr<Visual>(data_ptr, data_ptr.get());
}

void Visual::setMesh(std::shared_ptr<Mesh> mesh_) {
    std::unique_lock lk {mtx};
    mesh = mesh_;
}

std::shared_ptr<Mesh> Visual::getMesh() {
    std::unique_lock lk {mtx};
    return mesh;
}

void Visual::setMaterial(std::shared_ptr<Material> material_) {
    std::unique_lock lk {mtx};
    material = material_;
}

std::shared_ptr<Material> Visual::getMaterial() {
    std::unique_lock lk {mtx};
    return material;
}

} // namespace folk
