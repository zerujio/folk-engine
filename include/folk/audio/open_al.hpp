#ifndef FOLK_AUDIO__OPEN_AL_HPP
#define FOLK_AUDIO__OPEN_AL_HPP

#include "folk/error.hpp"

#include <AL/al.h>

#include <functional>
#include <type_traits>


/// Detalles de implementación
namespace Folk::al {

struct ALError : public Folk::RuntimeError {
    static const char* errorString(ALenum);

    ALError(ALenum error, const char* where, unsigned int line, const char* func) 
        : RuntimeError(errorString(error), where, line, func) 
    {}

    using Folk::RuntimeError::RuntimeError;
};

void checkErrors(const char* file, unsigned int line, const char* func);

template<typename alFunction, typename... Args>
auto call(const char* where, unsigned int line, const char* func,
          alFunction function, Args&&... args) 
-> decltype(function(args...))
{
    if constexpr (std::is_same_v<decltype(function(args...)), void>) {
        alGetError();
        function(std::forward<Args>(args)...);
        checkErrors(where, line, func);
    } else {
        alGetError();
        auto ret_val = function(std::forward<Args>(args)...);
        checkErrors(where, line, func);
        return ret_val;
    }
}

#define AL_CALL(func, ...) al::call(__FILE__, __LINE__, __PRETTY_FUNCTION__, func, __VA_ARGS__)

// Non owning handle for an OpenAL object
template<void (*alGen)(ALsizei, ALuint*), 
         void (*alDelete)(ALsizei, const ALuint*),
         ALboolean (*isValid)(ALuint)>
class ObjectHandle 
{
    const ALuint m_id;

protected:
    template<typename ReturnT>
    ReturnT get(void (*getter)(ALuint, ALenum, ReturnT*), ALenum property) const {
        ReturnT value;
        AL_CALL(getter, m_id, property, &value);
        return value;
    }

    template<typename ParamT>
    void set(void (*setter)(ALuint, ALenum, ParamT), ALenum property, ParamT value) const {
        AL_CALL(setter, m_id, property, value);
    }

public:
    ObjectHandle(ALuint id) : m_id(id) {}

    static ALuint createId() {
        ALuint id;
        AL_CALL(alGen, 1, &id);
        return id;
    }

    ALuint id() const {
        return m_id;
    }

    ALenum destroy() noexcept {
        alDelete(1, &m_id);
        return alGetError();
    }

    void destroyThrowing() {
        AL_CALL(alDelete, 1, &m_id);
    }
};

/// Wrapper para un buffer de OpenAL (non-owning)
class BufferManager : public ObjectHandle<alGenBuffers, alDeleteBuffers, alIsBuffer> {
public:
    using ObjectHandle::ObjectHandle;

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
        AL_CALL(alBufferData, id(), format, data, size, freq);
    }
};

} // namespace Folk::al

#endif // FOLK_AUDIO__OPEN_AL_HPP
