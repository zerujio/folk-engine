#include <utility>

#include "folk/render/visual.hpp"

#include "../core/engine.hpp"

#include "visual_data.hpp"
#include "renderer.hpp"

namespace Folk
{

std::shared_ptr<Visual> Visual::create() {
    return create(Mesh::createCube({0xff, 0xff, 0xff, 0xff}), Material::create());
}

std::shared_ptr<Visual> Visual::create(std::shared_ptr<Mesh> mesh_) {
    return create(std::move(mesh_), Material::create());
}

std::shared_ptr<Visual> Visual::create(std::shared_ptr<Material> material_) {
    return create(Mesh::createCube({0xff, 0xff, 0xff, 0xff}), std::move(material_));
}

std::shared_ptr<Visual> Visual::create(std::shared_ptr<Mesh> mesh_,
                                       std::shared_ptr<Material> material_)
{
    auto data_ptr = std::make_shared<VisualData>(std::move(mesh_), std::move(material_));
    return std::shared_ptr<Visual>(data_ptr, data_ptr.get());
}

void Visual::setMesh(std::shared_ptr<Mesh> mesh_) {
    std::unique_lock lk {mtx};
    mesh = std::move(mesh_);
}

std::shared_ptr<Mesh> Visual::getMesh() {
    std::unique_lock lk {mtx};
    return mesh;
}

void Visual::setMaterial(std::shared_ptr<Material> material_) {
    std::unique_lock lk {mtx};
    material = std::move(material_);
}

std::shared_ptr<Material> Visual::getMaterial() {
    std::unique_lock lk {mtx};
    return material;
}

} // namespace folk
