#include "folk/folk.hpp"
#include "folk/input/input.hpp"
#include "folk/render/visual_component.hpp"

#include <iostream>

static void update(folk::Scene&, double);

static folk::InputAction action {};

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

    scene.updateCallback = update;

    action.keys.emplace(folk::key_right_alt);
    action.keys.emplace(folk::key_left_alt);
}

void update(folk::Scene& scn, double delta) {
    if (action.state())
        std::cout << delta << "\n";
}