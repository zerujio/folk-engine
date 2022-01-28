#include "folk/audio/audio_source_component.hpp"

namespace Folk
{

std::shared_ptr<AudioClip> AudioSourcePtr::getAudioClip() const {
    return ref.audio_clip;
}

void AudioSourcePtr::setAudioClip(std::shared_ptr<AudioClip> new_clip) const {
    ref.audio_clip = std::move(new_clip);
    ref.source_manager.setBuffer(ref.audio_clip->buffer_mngr);
}

bool AudioSourcePtr::getLooping() const {
    return ref.source_manager.getLooping();
}

void AudioSourcePtr::setLooping(bool v) const {
    return ref.source_manager.setLooping(v);
}

void AudioSourcePtr::play() const {
    ref.source_manager.play();
}

void AudioSourcePtr::pause() const {
    ref.source_manager.pause();
}

void AudioSourcePtr::stop() const {
    ref.source_manager.stop();
}

void AudioSourcePtr::rewind() const {
    ref.source_manager.rewind();
}

} // namespace Folk
