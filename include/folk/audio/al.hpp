#ifndef FOLK_AUDIO__OPEN_AL_HPP
#define FOLK_AUDIO__OPEN_AL_HPP

#include "folk/utils/library_call.hpp"
#include "folk/utils/object_handle.hpp"

#include "AL/al.h"

/// Detalles de implementación
namespace Folk::al {

const char* errorString(ALenum);

struct ALError : public Error {
    using Error::Error;

    template<class... Args>
    explicit ALError(ALenum code, Args... args) : Error(errorString(code), args...) {}
};

using call = LibCall<ALError, alGetError>;

template<auto isValid>
using BaseHandle = ObjectHandle<call, isValid, ALuint>;

} // namespace Folk::al

#endif // FOLK_AUDIO__OPEN_AL_HPP
