//
// Created by sergio on 08-12-21.
//

#include "folk/folk.hpp"
#include "folk/script.hpp"
#include "folk/input.hpp"
#include "folk/render.hpp"

struct CameraScript final : public Folk::Script {

    using Script::Script;

    float speed {1.0f};

    void update(std::chrono::duration<float> delta) override {
        auto transform = this_entity.getComponent<Folk::TransformComponent>().value();
        Folk::Vec3 position = transform.position();
        float move_dist = speed * delta.count();

        if (Folk::getKey(Folk::Key::A) == Folk::InputState::Press) {
            position.x -= move_dist;
        }
        if (Folk::getKey(Folk::Key::D) == Folk::InputState::Press) {
            position.x += move_dist;
        }
        if (Folk::getKey(Folk::Key::W) == Folk::InputState::Press) {
            position.z += move_dist;
        }
        if (Folk::getKey(Folk::Key::S) == Folk::InputState::Press) {
            position.z -= move_dist;
        }

        if (position != transform.position())
            transform.position(position);
    }
};

struct CubeScript final : public Folk::Script {

    using Script::Script;

    Folk::Vec3 rotation_vector {};

    void update(std::chrono::duration<float> delta) override {
        auto transform = this_entity.getComponent<Folk::TransformComponent>().value();

        Folk::Vec3 rotation = transform.rotation();
        rotation += rotation_vector * delta.count();
        transform.rotation(rotation);
    }
};

Folk::EntityHandle createCube(Folk::EntityHandle parent, const char* name, std::shared_ptr<Folk::Visual> visual) {
    Folk::EntityHandle handle = parent.createChild(name);

    handle.getComponent<Folk::TransformComponent>()->scale({0.5f, 0.5f, 0.5f});
    handle.addComponent<Folk::VisualComponent>(visual);
    handle.addComponent<Folk::ScriptComponent>().addScript<CubeScript>();

    return handle;
}

void Folk::sceneInit(Scene& scene) {
    auto camera = scene.root().createChild("Camera");
    scene.setCamera(camera.addComponent<Folk::CameraComponent>());
    camera.getComponent<Folk::TransformComponent>()->position({0.0f, 0.0f, -3.0f});
    camera.addComponent<Folk::ScriptComponent>().addScript<CameraScript>().speed = 3.0f;

    auto visual = Folk::Visual::create(Folk::Mesh::create(Folk::ImmediateGeometry::createCube(0xffffffff)));

    auto box1 = createCube(scene.root(), "Box 1", visual);
    box1.getComponent<TransformComponent>()->position({-1.0f, 0.0f, 0.0f});
    auto script = box1.getComponent<ScriptComponent>()->getScript<CubeScript>();
    script->rotation_vector = {1.0f, 0.0f, 0.0f};

    auto box2 = createCube(scene.root(), "Box 2", visual);
    box2.getComponent<TransformComponent>()->position({1.0f, 0.0f, 0.0f});
    script = box2.getComponent<ScriptComponent>()->getScript<CubeScript>();
    script->rotation_vector = {0.0f, 1.0f, 0.0f};
}

void Folk::engineInit() {
    Engine::setWindowTitle("Script Example");
    Engine::setPerformanceMetricsEnabled(true);
}