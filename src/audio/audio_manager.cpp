#include "audio_manager.hpp"

#include "folk/audio/audio_source_component.hpp"

namespace Folk {

AudioManager::AudioManager(const ExceptionHandler &exception_handler)
{
    m_context.makeCurrent();
}

void AudioManager::update(const ExceptionHandler &exception_handler, SceneManager& scene_manager,
                          std::chrono::duration<double> delta) const noexcept
{
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
    Vec3 position {0.0f, 0.0f, 0.0f};
    Vec3 up {0.0f, 1.0f, 0.0f};
    Vec3 at {0.0f, 0.0f, 1.0f};
    Vec3 velocity {0.0f, 0.0f, 0.0f};

    if (scene_manager.camera() != entt::null) {
        Vec3 old_position {0.0f, 0.0f, 0.0f};
        FOLK_AL_CALL(alGetListener3f, AL_POSITION, &old_position.x, &old_position.y, &old_position.z);
        old_position.z *= -1;

        auto& camera_node = scene_manager.registry().get<SceneGraphNode>(scene_manager.camera());

        position = camera_node.transformMatrix() * Vec4(0.0f, 0.0f, 0.0f, 1.0f);
        velocity = (position - old_position) / static_cast<float>(delta.count());
        up = camera_node.transformMatrix() * Vec4(up, 1.0f);
        up -= position;
        at = camera_node.transformMatrix() * Vec4(at, 1.0f);
        at -= position;
    }

    FOLK_AL_CALL(alListener3f, AL_POSITION, position.x, position.y, -position.z);
    FOLK_AL_CALL(alListener3f, AL_VELOCITY, velocity.x, velocity.y, -velocity.z);

    float orientation[] = {at.x, at.y, -at.z, up.x, up.y, -up.z};
    FOLK_AL_CALL(alListenerfv, AL_ORIENTATION, orientation);

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
    Vec3 old_position {source_component.source_manager.getPosition()};

    // update current position
    Vec3 position {0.0f, 0.0f, 0.0f};
    position = node_component.transformMatrix() * Vec4(position, 1.0f);
    position.z *= -1;
    source_component.source_manager.setPosition(position);

    // calculate velocity as (position - old_position) / delta
    Vec3 velocity = (position - old_position) / delta.count();
    source_component.source_manager.setVelocity(velocity);

} catch (...) {
    exception_handler.catchException();
    return;
}

} // namespace Folk