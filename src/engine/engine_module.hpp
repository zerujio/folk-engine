#ifndef FOLK_ENGINE__ENGINE_MODULE_HPP
#define FOLK_ENGINE__ENGINE_MODULE_HPP

#include <string>
#include "folk/engine/error.hpp"

namespace folk
{

/* Virtual base class to represent engine modules. */
class EngineModule {
    friend class EngineSingleton;

public:
    EngineModule() = default;
    EngineModule(const EngineModule&) = delete;
    EngineModule& operator=(const EngineModule&) = delete;

    bool isRunning() {return initialized;}

protected:
    virtual void onStartUp() = 0;
    virtual void onShutDown() = 0;
    virtual const std::string& name() = 0;

private:
    void startUp();
    void shutDown();
    bool initialized {false};
};

} // namespace folk

#include "../utils/singleton.hpp"
#define FOLK_ENGINE_MODULE_SINGLETON(CLASS_NAME) \
    class CLASS_NAME : public EngineModule, public Singleton<CLASS_NAME>

#define FOLK_ENGINE_MODULE_NAME_FUNCTION(NAME_STRING) \
    const std::string& name() override\
    {static std::string _name = NAME_STRING; return _name;}

#endif//FOLK_ENGINE__ENGINE_MODULE_HPP