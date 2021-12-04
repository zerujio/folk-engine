#include "../core/engine_singleton.hpp"
#include "folk/audio/audio_source_component.hpp"

#include "audio_manager.hpp"

namespace Folk {

static void onAudioSourceConstruct(entt::registry& r, entt::entity e) {
    auto& audio_source = r.get<AudioSourceComponent>(e);
    AL_CALL(alGenSources, 1, &audio_source.source_handle);
}

static void onAudioSourceDestroy(entt::registry& r, entt::entity e) {
    auto& audio_source = r.get<AudioSourceComponent>(e);
    //AL_CALL(alSourcei, audio_source.source_handle, AL_BUFFER, 0);
    AL_CALL(alDeleteSources, 1, &audio_source.source_handle);
}

AudioManager::AudioManager() {
    m_context.makeCurrent();
}

void AudioManager::connectRegistry(entt::registry& reg) {
    reg.on_construct<AudioSourceComponent>().connect<onAudioSourceConstruct>();
    reg.on_destroy<AudioSourceComponent>().connect<onAudioSourceDestroy>();
}

} // namespace Folk