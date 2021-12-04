#include "open_alc.hpp"

namespace Folk::alc
{

const char* ALCError::errorString(ALCenum err) {
    switch (err)
    {
    case ALC_NO_ERROR:
        return "ALC_NO_ERROR";

    case ALC_INVALID_VALUE:
        return "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function";
        
    case ALC_INVALID_DEVICE:
        return "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function";
        
    case ALC_INVALID_CONTEXT:
        return "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function";
        
    case ALC_INVALID_ENUM:
        return "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function";
        
    case ALC_OUT_OF_MEMORY:
        return "ALC_OUT_OF_MEMORY: operation caused OpenAL to run out of memory";

    default:
        return "UNKNOWN ALC ERROR";
    }
}

void checkErrors(ALCdevice* device, const char* file, unsigned int line, const char* func) {
    auto err = alcGetError(device);

    if (err != ALC_NO_ERROR)
        throw ALCError(err, file, line, func);
}

// Device

DeviceManager::DeviceManager() {
    m_device = alcOpenDevice(nullptr);

    if (!m_device)
        FOLK_ERROR(ALCError, "Couldn't open default device");
}

DeviceManager::~DeviceManager() {
    alcCloseDevice(m_device);
}

// Context

ContextManager::ContextManager(DeviceManager& device) {
    m_context = alcCreateContext(device.handle(), nullptr);

    auto error = alcGetError(device.handle());

    if (error == ALC_INVALID_VALUE)
        FOLK_ERROR(ALCError, "ALC_INVALID_VALUE: An additional context can not be created for this device.");
    
    else if (error == ALC_INVALID_DEVICE)
        FOLK_ERROR(ALCError, "ALC_INVALID_DEVICE: The specified device is not a valid output device.");
}

ContextManager::~ContextManager() {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
}

void ContextManager::makeCurrent() {
    auto device = alcGetContextsDevice(m_context);

    ALC_CALL(device, alcMakeContextCurrent, m_context);
}

} // namespace alc