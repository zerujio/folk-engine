//
// Created by sergio on 28-01-22.
//

#ifndef INCLUDE_FOLK_AUDIO__AL_SOURCE_HPP
#define INCLUDE_FOLK_AUDIO__AL_SOURCE_HPP

#include "al.hpp"

#include "folk/utils/object_handle.hpp"
#include "folk/utils/object_manager.hpp"
#include "folk/audio/al_buffer.hpp"
#include "folk/math/vector.hpp"

namespace Folk::al {

class SourceHandle : public BaseHandle<alIsSource> {
public:
    /// Get current position of audio source.
    [[nodiscard]] Vec3 getPosition() const;

    /// Set the current position of audio source.
    void setPosition(Vec3 pos) const;

    /// Get velocity of the audio source.
    [[nodiscard]] Vec3 getVelocity() const;

    /// Set the velocity of the audio source.
    void setVelocity(Vec3 vel) const;

    /// Get direction.
    [[nodiscard]] Vec3 getDirection() const;

    /// Set direction.
    void setDirection(Vec3 dir) const;

    /// Bind an audio buffer.
    void setBuffer(BufferHandle buffer) const;

    /// Get currently bound audio buffer.
    [[nodiscard]] BufferHandle getBuffer() const;

    /// Unbind current buffer.
    void clearBuffer() const;

    /// Check if audio playback is set to loop.
    [[nodiscard]] bool getLooping() const;

    /// Enable/disable audio playback looping.
    void setLooping(bool) const;

    /// Start (or restart) audio playback.
    void play() const;

    /// Pause audio playback.
    void pause() const;

    /// Stop audio playback.
    void stop() const;

    /// rewind audio playback (restore source to initial state).
    void rewind() const;
};

using SourceManager = ObjectManager<SourceHandle, alGenSources, alDeleteSources>;

} // namespace Folk::al

#endif //INCLUDE_FOLK_AUDIO__AL_SOURCE_HPP
