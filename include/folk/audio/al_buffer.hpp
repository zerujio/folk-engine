//
// Created by sergio on 28-01-22.
//

#ifndef FOLK_AUDIO__AL_BUFFER_HPP
#define FOLK_AUDIO__AL_BUFFER_HPP

#include "al.hpp"
#include "folk/utils/object_handle.hpp"
#include "folk/utils/object_manager.hpp"

namespace Folk::al {

/// Wrapper para un buffer de OpenAL (non-owning)
class BufferHandle : public BaseHandle<alIsBuffer>{
public:

    [[nodiscard]] int frequency() const;

    [[nodiscard]] int bitDepth() const;

    /// Number of audio channels; only single channel audio can be positioned.
    [[nodiscard]] int channels() const;

    /// Size of buffer (in bytes).
    [[nodiscard]] int size() const;

    /// Copy audio data to buffer.
    void copyData(int format, const void * data, int size, int freq) const;

private:
    friend class SourceHandle;

    using ObjectHandle::ObjectHandle;
};

using BufferManager = ObjectManager<BufferHandle, alGenBuffers, alDeleteBuffers>;

} // namespace Folk::al

#endif //FOLK_AUDIO__AL_BUFFER_HPP
