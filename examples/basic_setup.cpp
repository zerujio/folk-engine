#include "folk/folk.hpp"
#include "folk/input/input.hpp"
#include "folk/render/visual_component.hpp"

#include <iostream>

static Folk::InputAction enable_metrics;

static void update(Folk::Scene& scn, double delta) {
    if (enable_metrics.state() == Folk::KeyState::Press)
        Folk::Engine::setPerformanceMetricsEnabled(true);
}

void Folk::engineInit() {
    Folk::Engine::setWindowTitle("Hello world!");
    Folk::Engine::setPerformanceMetricsEnabled(true);
}

void Folk::sceneInit(Folk::Scene &scene) {
    Node& square = scene.rootNode().createChild("Square");

    auto visual = Visual::create(
        Mesh::create(ImmediateGeometry::triangle()),
        Material::createDefaultMaterial()
    );

    auto& component = square.addComponent<VisualComponent>(visual);

    scene.updateCallback = update;

    enable_metrics.keys.emplace(Folk::Key::RightAlt);
    enable_metrics.keys.emplace(Folk::Key::LeftAlt);
}
