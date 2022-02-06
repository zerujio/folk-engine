//
// Created by sergio on 28-01-22.
//

#include "../../include/folk/audio/al_buffer.hpp"

namespace Folk::al {

int BufferHandle::frequency() const {
    return get<int, alGetBufferi>(AL_FREQUENCY);
}

int BufferHandle::bitDepth() const {
    return get<int, alGetBufferi>(AL_BITS);
}

int BufferHandle::channels() const {
    return get<int, alGetBufferi>(AL_CHANNELS);
}

int BufferHandle::size() const {
    return get<int, alGetBufferi>(AL_SIZE);
}

void BufferHandle::copyData(const int format, const void *data, const int size, const int freq) const {
    Call::slow(alBufferData)(id(), format, data, size, freq);
}

}