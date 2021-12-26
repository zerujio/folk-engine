#include "folk/audio/audio_source_component.hpp"

#include "audio_manager.hpp"

#include <bgfx/bgfx.h>
#include <bx/math.h>

namespace Folk {

static void onAudioSourceConstruct(entt::registry& r, entt::entity e) {
    auto& audio_source = r.get<AudioSourceComponent>(e);
    AL_CALL(alGenSources, 1, &audio_source.source_handle);
}

static void onAudioSourceDestroy(entt::registry& r, entt::entity e) {
    auto& audio_source = r.get<AudioSourceComponent>(e);
    AL_CALL(alDeleteSources, 1, &audio_source.source_handle);
}

AudioManager::AudioManager() {
    m_context.makeCurrent();
}

void AudioManager::connectRegistry(entt::registry& reg) {
    reg.on_construct<AudioSourceComponent>().connect<onAudioSourceConstruct>();
    reg.on_destroy<AudioSourceComponent>().connect<onAudioSourceDestroy>();
}

void AudioManager::update(const ExceptionHandler &exception_handler,
                          SceneManager& scene_manager, std::chrono::duration<double> delta) const noexcept {
    updateListener(exception_handler, scene_manager, delta);

    auto update_source = [exception_handler, delta](SceneGraphNode& node, const AudioSourceComponent& src) {
        return updateSource(exception_handler, node, src, delta);
    };
    scene_manager.registry().view<SceneGraphNode, const AudioSourceComponent>().each(update_source);
}

void AudioManager::updateListener(const ExceptionHandler& exception_handler,
                                  SceneManager &scene_manager,
                                  std::chrono::duration<double> delta) noexcept
try {
    bx::Vec3 position {0.0f, 0.0f, 0.0f};
    bx::Vec3 up {0.0f, 1.0f, 0.0f};
    bx::Vec3 at {0.0f, 0.0f, 1.0f};
    bx::Vec3 velocity {0.0f, 0.0f, 0.0f};

    if (scene_manager.camera() != entt::null) {
        bx::Vec3 old_position {0.0f, 0.0f, 0.0f};
        AL_CALL(alGetListener3f, AL_POSITION, &old_position.x, &old_position.y, &old_position.z);
        old_position.z *= -1;

        auto& camera_node = scene_manager.registry().get<SceneGraphNode>(scene_manager.camera());

        position = bx::mul({0.0f, 0.0f, 0.0f}, camera_node.transformMatrix());
        velocity = bx::div(bx::sub(position, old_position), static_cast<float>(delta.count()));
        up = bx::sub(bx::mul(up, camera_node.transformMatrix()), position);
        at = bx::sub(bx::mul(at, camera_node.transformMatrix()), position);
    }

    AL_CALL(alListener3f, AL_POSITION, position.x, position.y, -position.z);
    AL_CALL(alListener3f, AL_VELOCITY, velocity.x, velocity.y, -velocity.z);

    float orientation[] = {at.x, at.y, -at.z, up.x, up.y, -up.z};
    AL_CALL(alListenerfv, AL_ORIENTATION, orientation);

} catch (...) {
    exception_handler.catchException();
    return;
}

void AudioManager::updateSource(const ExceptionHandler &exception_handler,
                                SceneGraphNode& node_component,
                                const AudioSourceComponent& source_component,
                                std::chrono::duration<float> delta)
                                noexcept
try {
    // get old position
    bx::Vec3 old_position {0.0f, 0.0f, 0.0f};
    AL_CALL(alGetSource3f, source_component.source_handle, AL_POSITION, &old_position.x, &old_position.y, &old_position.z);

    // calculate current position
    bx::Vec3 position {0.0f, 0.0f, 0.0f};
    position = bx::mul(position, node_component.transformMatrix());
    position.z *= -1;
    AL_CALL(alSource3f, source_component.source_handle, AL_POSITION, position.x, position.y, position.z);

    // calculate velocity as (position - old_position) / delta
    bx::Vec3 velocity = bx::div(bx::sub(position, old_position), delta.count());
    AL_CALL(alSource3f, source_component.source_handle, AL_VELOCITY, velocity.x, velocity.y, velocity.z);

} catch (...) {
    exception_handler.catchException();
    return;
}

} // namespace Folk