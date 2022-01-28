//
// Created by sergio on 28-01-22.
//

#include "folk/audio/al_source.hpp"

namespace Folk::al {


Vec3 SourceHandle::getPosition() const {
    return getV<Vec3, alGetSourcefv>(AL_POSITION);
}

void SourceHandle::setPosition(const Vec3 pos) const {
    setV<Vec3, alSourcefv>(AL_POSITION, pos);
}

Vec3 SourceHandle::getVelocity() const {
    return getV<Vec3, alGetSourcefv>(AL_VELOCITY);
}

void SourceHandle::setVelocity(Vec3 vel) const {
    setV<Vec3, alSourcefv>(AL_VELOCITY, vel);
}

Vec3 SourceHandle::getDirection() const {
    return getV<Vec3, alGetSourcefv>(AL_DIRECTION);
}

void SourceHandle::setDirection(Vec3 dir) const {
    setV<Vec3, alSourcefv>(AL_DIRECTION, dir);
}

void SourceHandle::setBuffer(BufferHandle buffer) const {
    set<ALint, alSourcei>(AL_BUFFER, buffer.m_id);
}

void SourceHandle::clearBuffer() const {
    set<ALint, alSourcei>(AL_BUFFER, 0);
}

BufferHandle SourceHandle::getBuffer() const {
    return BufferHandle(get<ALint, alGetSourcei>(AL_BUFFER));
}

bool SourceHandle::getLooping() const {
    return get<int, alGetSourcei>(AL_LOOPING);
}

void SourceHandle::setLooping(const bool value) const {
    set<int, alSourcei>(AL_LOOPING, value);
}

void SourceHandle::play() const {
    FOLK_AL_CALL(alSourcePlay, m_id);
}

void SourceHandle::pause() const {
    FOLK_AL_CALL(alSourcePause, m_id);
}

void SourceHandle::stop() const {
    FOLK_AL_CALL(alSourcePause, m_id);
}

void SourceHandle::rewind() const {
    FOLK_AL_CALL(alSourcePause, m_id);
}


} // namespace Folk::al
