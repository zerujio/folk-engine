#include "folk/folk.hpp"
#include "folk/render/visual_component.hpp"

void folk::engineInit() {
    folk::engine::setWindowTitle("Hello world!");
}

void folk::sceneInit(folk::Scene &scene) {
    Node& triangle = scene.addNode("Triangle");

    auto visual = Visual::create(
        Mesh::create(ImmediateGeometry::triangle()),
        Material::createDefaultMaterial()
    );

    auto& component = triangle.addComponent<VisualComponent>(visual);
}