//
// Created by sergio on 17-12-21.
//

#include "folk/folk.hpp"
#include "folk/input.hpp"
#include "folk/render.hpp"
#include "folk/script.hpp"
#include "folk/ai.hpp"
#include "folk/input.hpp"

#include <chrono>

struct ControlScript final : public Folk::Script {
    using Script::Script;

    float speed = {5.0f};

    void update(std::chrono::duration<float> delta) override {
        Folk::Vec3 direction {};

        if (Folk::Input::get(Folk::Key::A) == Folk::InputState::Press)
            direction.x -= 1.0f;

        if (Folk::Input::get(Folk::Key::D) == Folk::InputState::Press)
            direction.x += 1.0f;

        if (Folk::Input::get(Folk::Key::W) == Folk::InputState::Press)
            direction.z += 1.0f;

        if (Folk::Input::get(Folk::Key::S) == Folk::InputState::Press)
            direction.z -= 1.0f;

        if (direction.x != 0.0f or direction.z != 0.0f) {
            auto transform = this_entity.getComponent<Folk::TransformComponent>().value();
            Folk::Vec3 position = transform.position();
            Folk::Vec3 velocity = direction.normalized() * speed;
            transform.position(position + velocity * delta.count());
        }
    }
};

// cube behavior tree;
struct MoveTowards final {
    const Folk::Vec3& target;
    float margin {0.1f};
    float speed {4.0f};

    MoveTowards(const Folk::Vec3& target_) : target(target_) {}

    Folk::BehaviorTreeStatus update(Folk::EntityHandle entity, Folk::FloatDelta delta) const {
        auto transform = entity.getComponent<Folk::TransformComponent>().value();
        auto current_position = transform.position();
        auto vec_to_target = target - current_position;
        float dist = vec_to_target.length();

        if (dist < speed * delta.count()) {
            transform.position(target);
            return Folk::BehaviorTreeStatus::Success;
        }

        auto direction = vec_to_target / dist;
        float smoothing = (dist > 2 * margin) ? 1 : dist / (2 * margin);
        transform.position(current_position + direction * (smoothing * speed * delta.count()));

        return Folk::BehaviorTreeStatus::Running;
    }
};

struct IsNear final {
    const Folk::Vec3& target;
    float distance {1.0f};

    IsNear(const Folk::Vec3& target_) : target(target_) {}

    Folk::BehaviorTreeStatus update(Folk::EntityHandle entity, Folk::FloatDelta delta) const {
        auto transform = entity.getComponent<Folk::TransformComponent>().value();

        if ((target - transform.position()).lengthSquared() <= distance * distance)
            return Folk::BehaviorTreeStatus::Success;
        return Folk::BehaviorTreeStatus::Failure;
    }
};

class Follow final {
    Folk::FallbackBT<IsNear, MoveTowards> fallback;
    Folk::Vec3 target_position;

public:
    Folk::EntityHandle target_entity;

    Follow(const Folk::EntityHandle& entity) : target_entity(entity), fallback(target_position, target_position) {}

    Folk::BehaviorTreeStatus update(Folk::EntityHandle entity, Folk::FloatDelta delta) {
        target_position = target_entity.getComponent<Folk::TransformComponent>()->position();
        return fallback.update(entity, delta);
    }
};

void Folk::engineInit() {
    Folk::Engine::setWindowTitle("Behavior trees");
    Folk::Engine::setPerformanceMetricsEnabled(true);
}

void Folk::sceneInit(Scene &scene) {
    Folk::EntityHandle camera = scene.root().createChild("Camera");
    auto camera_transform = camera.getComponent<Folk::TransformComponent>();
    camera_transform->position({0.0f, 20.0f, 0.0f});
    camera_transform->rotation({-3.14f / 2, 0.0f, 0.0f});
    scene.setCamera(camera.addComponent<Folk::CameraComponent>());

    Folk::EntityHandle red_cube = scene.root().createChild("Red cube");
    auto red_visual = Folk::Visual::create(
            Folk::Mesh::create(Folk::ImmediateGeometry::createCube(0xff0000ff)));
    red_cube.addComponent<Folk::VisualComponent>(red_visual);
    red_cube.addComponent<Folk::ScriptComponent>().addScript<ControlScript>();

    auto white_visual =
            Folk::Visual::create(Folk::Mesh::create(Folk::ImmediateGeometry::createCube(0xffffffff)));

    auto white_cube = scene.root().createChild("White cube");
    auto transform = white_cube.getComponent<TransformComponent>().value();
    transform.position({5.0F, 0.0f, 5.0f});
    transform.scale({0.5f, 0.5f, 0.5f});
    white_cube.addComponent<VisualComponent>(white_visual);
    white_cube.addComponent<Folk::BehaviorTreeComponent>().setBehaviorTree<Follow>(red_cube);
}