#include "folk/folk.hpp"
#include "folk/render.hpp"
#include "folk/audio.hpp"
#include "folk/input.hpp"
#include "input.hpp"

#include <cmath>

void onUpdate(Folk::Scene&, float);

void Folk::engineInit() {
    // pass
}

void Folk::sceneInit(Folk::Scene &scene) {
    using namespace Folk;

    // Este objeto será la fuente del sonido
    auto audio_source = scene.root().createChild("Audio source");

    auto cube_mesh = Mesh::create(ImmediateGeometry::createCube(0xffffffff));
    auto visual = Visual::create(cube_mesh);
    audio_source.addComponent<VisualComponent>(visual);

    // Se carga un clip de audio
    auto audio_clip = AudioClip::createFromFile("example_audio.wav");
    auto audio_comp = audio_source.addComponent<AudioSourceComponent>();
    audio_comp.setAudioClip(audio_clip);
    audio_comp.setLooping(true);
    audio_comp.play();

    // Creamos la cámara, el AudioListener toma la posición y
    // orientacion de la cámara.
    auto camera = scene.root().createChild("Camera");
    auto camera_comp = camera.addComponent<CameraComponent>();
    scene.setCamera(camera_comp);

    camera.getComponent<TransformComponent>()->position({0.0f, 0.0f, -3.0f});

    scene.updateCallback = onUpdate;
}

void onUpdate(Folk::Scene& scene, float deltaT) {

    auto dist = deltaT * 2.5;

    auto transform = scene.root().getChild("Camera")
                                 ->getComponent<Folk::TransformComponent>();
    auto pos = transform->position();

    if (Folk::Input::get(Folk::Key::W) == Folk::InputState::Press) {
        pos.z += dist;
    }

    if (Folk::Input::get(Folk::Key::S) == Folk::InputState::Press) {
        pos.z -= dist;
    }

    if (Folk::Input::get(Folk::Key::D) == Folk::InputState::Press) {
        pos.x += dist;
    }

    if (Folk::Input::get(Folk::Key::A) == Folk::InputState::Press) {
        pos.x -= dist;
    }

    if (transform->position() != pos)
        transform->position(pos);

    auto rot = transform->rotation();

    if (Folk::Input::get(Folk::Key::Q) == Folk::InputState::Press) {
        rot.y += dist;
    }

    if (Folk::Input::get(Folk::Key::E) == Folk::InputState::Press) {
        rot.y -= dist;
    }

    if (rot != transform->rotation())
        transform->rotation(rot);

    // move cube up and down
    static float angle = 0.0f;
    angle += deltaT;
    auto cam = scene.root().getChild("Audio source");
    if (cam)
        cam->getComponent<Folk::TransformComponent>()->position({std::sin(angle) * 3.0f, 0.0f, 0.0f});
}