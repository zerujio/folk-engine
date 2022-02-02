//
// Created by sergio on 21-12-21.
//

#include "folk/folk.hpp"
#include "folk/render.hpp"
#include "folk/input.hpp"
#include "folk/ai.hpp"
#include "folk/audio.hpp"
#include "folk/log.hpp"
#include "folk/script.hpp"

#include <cmath>
#include <cstdlib>

using namespace Folk;

// Esta función es invocada antes de inicializar la escena, pero después de inicializar el engine
void Folk::engineInit() {
    Game::setWindowTitle("Demo!");
    Game::setPerformanceMetricsEnabled(true);
}

// BehaviorTree utilizado por el cubo naranja
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

        if (glm::length(target - transform.position()) <= distance)
            return Folk::BehaviorTreeStatus::Success;
        return Folk::BehaviorTreeStatus::Failure;
    }
};

// Este BT hace que la entidad asociada siga a la target_entity
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

// Retorna la posición aproximada del mouse
Vec3 getMousePosition() {
    constexpr float scale = 2.5f;
    constexpr float width = 800;
    constexpr float height = 600;

    auto coords = Input::Cursor::getPosition();

    Vec3 position {(float(coords.x) / width) * 8 * scale - 8 * scale / 2,
                   0.0f,
                   (float(coords.y) / height) * 6 * scale - 6 * scale / 2};

    return position;
}

// Crear cubos blancos

// Esta función mantiene un weak_ptr al Visual utilizado por los cubos blancos.
std::shared_ptr<Visual> getWhiteCubeVisual() {
    static std::weak_ptr<Visual> visual_weak;
    std::shared_ptr<Visual> visual_shared;

    if (visual_weak.expired()) {
        auto mesh = Mesh::create(ImmediateGeometry::createCube(0xffffffff));
        visual_shared = Visual::create(mesh);
        visual_weak = visual_shared;
    } else {
        visual_shared = std::shared_ptr<Visual>(visual_weak);
    }

    return visual_shared;
}

EntityHandle createWhiteCube(EntityHandle parent) {
    auto handle = parent.createChild("White Cube");
    handle.addComponent<VisualComponent>(getWhiteCubeVisual());
    return handle;
}

// Este script hace que los cubos cambien de tamaño
struct WhiteScript final : public Folk::Script {
    using Script::Script;

    float angle {0.0f};

    void update(std::chrono::duration<float> delta) override {
        auto tr = this_entity.getComponent<Folk::TransformComponent>().value();

        angle += delta.count();
        tr.scale(Vec3(.5f, .5f, .5f) * std::sin(angle) + Vec3(1.0f, 1.0f, 1.0f));
    }
};

struct CreatorScript final : public Folk::Script {
    using Script::Script;

    std::shared_ptr<AudioClip> clip;

    void update(std::chrono::duration<float> delta) override {}

    // Invocada cuando se hace click derecho.
    void onRightClick(InputState state) {
        if (state == InputState::Press)
            return;

        // crea una nueva entidad
        auto handle = createWhiteCube(this_entity);
        handle.getComponent<TransformComponent>()->position(getMousePosition());

        // añade una fuente sonora
        auto audio_src = handle.addComponent<AudioSourceComponent>();
        audio_src.setAudioClip(clip);
        audio_src.play(); // reproduce el sonido

        // añade el script
        auto& script = handle.addComponent<ScriptComponent>().addScript<WhiteScript>();
        script.angle = float(std::rand())/RAND_MAX;
    }
};

// Este script hace que el cubo naranjo rote
struct OrangeScript final : public Folk::Script {

    using Script::Script;

    Folk::Vec3 rotation_vector {};

    void update(std::chrono::duration<float> delta) override {
        // Esto hace rotar el cubo
        auto transform = this_entity.getComponent<Folk::TransformComponent>().value();

        Folk::Vec3 rotation = transform.rotation();
        rotation += rotation_vector * delta.count();
        transform.rotation(rotation);
    }
};

struct TargetScript final : public Folk::Script {
    using Script::Script;

    void update(std::chrono::duration<float> delta) override {}

    // Mueve el target que el cubo naranja persigue
    void onClick(InputState state) {
        if (state == InputState::Press)
            return;

        this_entity.getComponent<TransformComponent>()->position(getMousePosition());
        this_entity.getComponent<AudioSourceComponent>()->play();
    }

};

void Folk::sceneInit(Scene &scene) {
    Log::warning() << "Esta demo utiliza los archivos 'click.wav' y 'ding.wav'! (Están disponibles en la carpeta examples/assets)\n";

    // se configura la cámara con una vista top-down.
    auto camera = scene.root().createChild("Camera");
    {
        auto tr = camera.getComponent<Folk::TransformComponent>().value();
        tr.rotation({3.14f / 2, 0.0f, 0.0f});
        tr.position({0.0f, -15.0f, 0.0f});
    }
    scene.setCamera(camera.addComponent<Folk::CameraComponent>());

    // se crea el cubo naranja
    auto cube = createWhiteCube(scene.root());
    auto visual = Visual::create(Mesh::create(ImmediateGeometry::createCube(0xff0088ff)));
    cube.getComponent<VisualComponent>()->setVisual(visual);                    // se setea un Visual color naranja
    cube.getComponent<TransformComponent>()->scale({1.1f, 1.1f, 1.1f});         // se aumenta la escala un 10%
    // se añade el script de rotación
    auto &script = cube.addComponent<ScriptComponent>().addScript<OrangeScript>();
    script.rotation_vector = {1.0f, 0.0f, .5f};

    // se crea una "entidad objetivo" sin representación visual
    auto target_entity = scene.root().createChild("Target entity");
    auto audio_clip = AudioClip::createFromFile("click.wav");
    target_entity.addComponent<AudioSourceComponent>().setAudioClip(audio_clip); // se añade un AudioSource

    // se añade un BehaviorTree al cubo naranja para que siga a la entidad objetivo
    auto& bt = cube.addComponent<BehaviorTreeComponent>().setBehaviorTree<Follow>(target_entity);

    // se crea una "acción" de input y se le añade un callback.
    // Esto hace que el objetivo cambie de posición cuando se hace click izquierdo.
    auto& clickAction = scene.input.actions.create("onClick");
    clickAction.bind(MouseButton::Left);
    // Se añade el script que mueve el cubo naranja.
    auto& target_script = target_entity.addComponent<ScriptComponent>().addScript<TargetScript>();
    clickAction.connect<&TargetScript::onClick>(target_script);

    // se crea otra acción
    auto& createAction = scene.input.actions.create("onCreate");
    createAction.bind(MouseButton::Right);
    // ... y se le asocia otro callback. Este hace que aparezcan cubos blancos cuando se hace click derecho.
    auto ding_clip = AudioClip::createFromFile("ding.wav");
    auto& root_script = scene.root().addComponent<ScriptComponent>().addScript<CreatorScript>();
    root_script.clip = ding_clip;
    createAction.connect<&CreatorScript::onRightClick>(root_script);
}