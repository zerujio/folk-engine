#include "alc.hpp"
#include "folk/log.hpp"

namespace Folk::alc
{

const char* errorString(ALCenum error) {
    switch (error)
    {
    case ALC_NO_ERROR:
        return "ALC_NO_ERROR";

    case ALC_INVALID_VALUE:
        return "ALC_INVALID_VALUE";
        
    case ALC_INVALID_DEVICE:
        return "ALC_INVALID_DEVICE";
        
    case ALC_INVALID_CONTEXT:
        return "ALC_INVALID_CONTEXT";
        
    case ALC_INVALID_ENUM:
        return "ALC_INVALID_ENUM";
        
    case ALC_OUT_OF_MEMORY:
        return "ALC_OUT_OF_MEMORY";

    default:
        return "UNKNOWN ALC ERROR";
    }
}

std::optional<const char *> getError(ALCdevice* device) noexcept {
    auto err = alcGetError(device);

    if (err)
        return {errorString(err)};
    else
        return {};
}

// Device

DeviceManager::DeviceManager() {
    m_device = alcOpenDevice(nullptr);

    if (!m_device)
        throw ALCError("[ALC ERROR] Failed to open default device.");
}

DeviceManager::~DeviceManager() noexcept {
    if (!alcCloseDevice(m_device)) {
        Log::error() << "[ALC_ERROR] Couldn't close device: there may be contexts and/or buffers that have not been destroyed.";
    }
}

// Context

ContextManager::ContextManager(DeviceManager& device) {
    m_context = call::slow(alcCreateContext, device.handle())(device.handle(), nullptr);
}

ContextManager::~ContextManager() {
    alcMakeContextCurrent(nullptr);

    call::slowNoExcept(alcDestroyContext, alcGetContextsDevice(m_context))(m_context);
}

void ContextManager::makeCurrent() {
    call::slow(alcMakeContextCurrent, alcGetContextsDevice(m_context))(m_context);
}

} // namespace alc