#include "folk/audio/al.hpp"
#include "folk/log.hpp"

namespace Folk::al {

const char* errorString(const ALenum error) {
    switch (error)
    {
    case AL_NO_ERROR:
        return "AL_NO_ERROR";

    case AL_INVALID_NAME:
        return "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";

    case AL_INVALID_ENUM:
        return "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
    
    case AL_INVALID_VALUE:
        return "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";

    case AL_INVALID_OPERATION:
        return "AL_INVALID_OPERATION: the requested operation is not valid";
        
    case AL_OUT_OF_MEMORY:
        return "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory";
        
    default:
        return "UNKNOWN AL ERROR";
    }
}

std::optional<const char *> getError() {
    auto error = alGetError();
    if (error)
        return {errorString(error)};
    return {};
}

} // namespace al