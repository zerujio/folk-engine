#ifndef FOLK_AUDIO__OPEN_AL_HPP
#define FOLK_AUDIO__OPEN_AL_HPP

#include "audio_error.hpp"

#include <AL/al.h>

#include <functional>
#include <type_traits>

namespace al {

const char* errorString(const ALenum);

void checkErrors();

template<typename alFunction, typename... Args>
auto call(alFunction function, Args&&... args) -> decltype(function(args...))
{
    if constexpr (std::is_same_v<decltype(function(args...)), void>) {
        function(std::forward<Args>(args)...);
        checkErrors();
    } else {
        auto ret_val = function(std::forward<Args>(args)...);
        checkErrors();
        return ret_val;
    }
}

template<void (*alGen)(ALsizei, ALuint*), void (*alDelete)(ALsizei, const ALuint*)>
class Object {
    ALuint m_handle;

protected:
    ALuint handle() const {
        return m_handle;
    }
    
    template<typename ReturnT>
    ReturnT get(void (*getter)(ALuint, ALenum, ReturnT*), ALenum property) const {
        ReturnT value;
        call(getter, property, &value);
        return value;
    }

public:
    Object() {
        call(alGen, 1, &m_handle);
    }

    ~Object() {
        call(alDelete, 1, &m_handle);
    }
};

/// Wrapper para un buffer de OpenAL
class Buffer : public Object<alGenBuffers, alDeleteBuffers> {
public:
    ALint frequency() const {
        return get(alGetBufferi, AL_FREQUENCY);
    }

    ALint bitDepth() const {
        return get(alGetBufferi, AL_BITS);
    }

    // Número de canales de audio. De acuerdo a la especificación, sólo los clips
    // mono-canal pueden ser posicionados.
    ALint channels() const {
        return get(alGetBufferi, AL_CHANNELS);
    }

    // tamaño del buffer en bytes.
    ALint size() const {
        return get(alGetBufferi, AL_SIZE);
    }

    void copyData(const ALenum format, 
                  const ALvoid* data, 
                  const ALsizei size, 
                  const ALsizei freq) const 
    {
        call(alBufferData, handle(), format, data, size, freq);
    }
};

} // namespace al

#endif // FOLK_AUDIO__OPEN_AL_HPP
