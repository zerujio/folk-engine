#ifndef FOLK_AUDIO__OPEN_ALC_HPP
#define FOLK_AUDIO__OPEN_ALC_HPP

#include "folk/error.hpp"
#include "folk/utils/library_call.hpp"

#include <AL/alc.h>

#include <functional>
#include <type_traits>

namespace Folk::alc
{

const char* errorString(ALCenum error);

struct ALCError : public Error {
    explicit ALCError(ALCenum error, source_location loc = source_location::current())
    : Error(errorString(error), loc) {}

    using Error::Error;
};

std::optional<const char *> getError(ALCdevice* device) noexcept;

using call = LibCall<getError, ALCdevice*>;

class DeviceManager {

    ALCdevice* m_device {nullptr};

public:

    /// open default device
    DeviceManager();

    /// take ownership of device
    explicit DeviceManager(ALCdevice* device) : m_device(device) {}

    /// Close owned device, if any.
    ~DeviceManager() noexcept;

    DeviceManager(const DeviceManager&) = delete;
    DeviceManager& operator=(const DeviceManager&) = delete;

    [[nodiscard]] ALCdevice* handle() const { return m_device; }
};

class ContextManager {

    ALCcontext* m_context {nullptr};

public:
    // create context on device
    explicit ContextManager(DeviceManager& device);
    ~ContextManager();

    ContextManager(ContextManager&) = delete;
    ContextManager& operator=(ContextManager&) = delete;

    void makeCurrent();
};

} // namespace alc


#endif // FOLK_AUDIO__OPEN_ALC_HPP