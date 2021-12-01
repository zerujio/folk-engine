#include "folk/folk.hpp"
#include "folk/render/render.hpp"
#include "folk/audio/audio.hpp"
#include "folk/input/input.hpp"

void onUpdate(Folk::Scene&, double);

void Folk::sceneInit(Folk::Scene &scene) {
    using namespace Folk;

    // Este objeto será la fuente del sonido
    auto audio_source = scene.root().createChild("Audio source");

    auto cube_mesh = Mesh::create(ImmediateGeometry::createCube(0xffffffff));
    auto visual = Visual::create(cube_mesh);
    audio_source.addComponent<VisualComponent>(visual);

    // Se carga un clip de audio
    auto audio_clip = AudioClip::createFromFile("example_audio.flac");
    audio_source.addComponent<AudioSourceComponent>().setClip(audio_clip);

    // Creamos la cámara
    auto camera = scene.root().createChild("Camera");
    auto camera_comp = camera.addComponent<CameraComponent>();
    scene.setCamera(camera_comp);

    camera.getComponent<TransformComponent>()->position({0.0f, 0.0f, -3.0f});

    // Añadimos un audio listener a la camara
    camera.addComponent<AudioListenerComponent>();

    scene.updateCallback = onUpdate;
}

void onUpdate(Folk::Scene& scene, double deltaT) {

    auto dist = deltaT * 2.5;

    auto transform = scene.root().getChild("Camera")
                                 ->getComponent<Folk::TransformComponent>();
    auto pos = transform->position();

    if (Folk::getKey(Folk::Key::W) == Folk::InputState::Press) {
        pos.z += dist;
    }

    if (Folk::getKey(Folk::Key::S) == Folk::InputState::Press) {
        pos.z -= dist;
    }

    if (Folk::getKey(Folk::Key::D) == Folk::InputState::Press) {
        pos.x += dist;
    }

    if (Folk::getKey(Folk::Key::A) == Folk::InputState::Press) {
        pos.x -= dist;
    }

    if (transform->position() != pos)
        transform->position(pos);
}