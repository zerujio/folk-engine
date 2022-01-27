#ifndef FOLK_AUDIO__OPEN_ALC_HPP
#define FOLK_AUDIO__OPEN_ALC_HPP

#include "folk/error.hpp"

#include <AL/alc.h>

#include <functional>
#include <type_traits>

namespace Folk::alc
{

struct ALCError : public RuntimeError {
    static const char* errorString(ALCenum);

    ALCError(ALCenum error, const char* where, unsigned int line, const char* func) 
        : RuntimeError(errorString(error), where, line, func) 
    {}

    using RuntimeError::RuntimeError;
};

void checkErrors(ALCdevice*, const char* file, unsigned int line, const char* func);

template<typename alcFunction, typename... Args>
auto call(const char* file, unsigned int line, const char* func,
          ALCdevice* err_device, alcFunction function, Args&&... args) 
{
    if constexpr (std::is_same_v<void, decltype(function(args...))>) {
        function(std::forward<Args>(args)...);
        checkErrors(err_device, file, line, func);
    } else {
        auto value = function(std::forward<Args>(args)...);
        checkErrors(err_device, file, line, func);
        return value;
    }
}

#define ALC_CALL(device, function, ...) alc::call(__FILE__, __LINE__, __PRETTY_FUNCTION__, device, function, __VA_ARGS__)

class DeviceManager {

    ALCdevice* m_device {nullptr};

public:

    /// open default device
    DeviceManager();

    /// take ownership of device
    DeviceManager(ALCdevice* device) : m_device(device) {}

    /// Close owned device, if any.
    ~DeviceManager();

    DeviceManager(const DeviceManager&) = delete;
    DeviceManager& operator=(const DeviceManager&) = delete;

    ALCdevice* handle() const { return m_device; }
};

class ContextManager {

    ALCcontext* m_context {nullptr};

public:
    // create context on device
    ContextManager(DeviceManager& device);
    ~ContextManager();

    ContextManager(ContextManager&) = delete;
    ContextManager& operator=(ContextManager&) = delete;

    void makeCurrent();
};

} // namespace alc


#endif // FOLK_AUDIO__OPEN_ALC_HPP