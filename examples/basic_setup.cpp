#include "folk/folk.hpp"
#include "folk/input/input.hpp"
#include "folk/render/visual_component.hpp"

#include <iostream>

static Folk::InputAction action {};

static void update(Folk::Scene& scn, double delta) {
    if (action.state())
        std::cout << delta << "\n";
}

void Folk::engineInit() {
    Folk::Engine::setWindowTitle("Hello world!");
}

void Folk::sceneInit(Folk::Scene &scene) {
    Node& square = scene.rootNode().createChild("Square");

    auto visual = Visual::create(
        Mesh::create(ImmediateGeometry::triangle()),
        Material::createDefaultMaterial()
    );

    auto& component = square.addComponent<VisualComponent>(visual);

    scene.updateCallback = update;

    action.keys.emplace(Folk::key_right_alt);
    action.keys.emplace(Folk::key_left_alt);
}
