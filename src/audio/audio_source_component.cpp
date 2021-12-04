#include "folk/audio/audio_source_component.hpp"

namespace Folk
{

std::shared_ptr<AudioClip> AudioSourcePtr::getAudioClip() const {
    return ref.audio_clip;
}

void AudioSourcePtr::setAudioClip(std::shared_ptr<AudioClip> new_clip) const {
    ref.audio_clip = new_clip;
    AL_CALL(alSourcei, ref.source_handle, AL_BUFFER, ref.audio_clip->buffer_mngr.id());
}

bool AudioSourcePtr::getLooping() const {
    ALint ret;
    AL_CALL(alGetSourcei, ref.source_handle, AL_LOOPING, &ret);
    return ret;
}

void AudioSourcePtr::setLooping(bool v) const {
    AL_CALL(alSourcei, ref.source_handle, AL_LOOPING, v);
}

void AudioSourcePtr::play() const {
    AL_CALL(alSourcePlay, ref.source_handle);
}

void AudioSourcePtr::pause() const {
    AL_CALL(alSourcePause, ref.source_handle);
}

void AudioSourcePtr::stop() const {
    AL_CALL(alSourceStop, ref.source_handle);
}

void AudioSourcePtr::rewind() const {
    AL_CALL(alSourceRewind, ref.source_handle);
}

} // namespace Folk
