#ifndef FOLK_AUDIO__OPEN_AL_HPP
#define FOLK_AUDIO__OPEN_AL_HPP

#include "folk/utils/library_call.hpp"
#include "folk/utils/object_handle.hpp"

#include "AL/al.h"

/// Detalles de implementación
namespace Folk::al {

const char* errorString(ALenum);

std::optional<const char*> getError();

using call = LibCall<getError>;

template<auto isValid>
using BaseHandle = ObjectHandle<call, isValid, ALuint>;

} // namespace Folk::al

#endif // FOLK_AUDIO__OPEN_AL_HPP
