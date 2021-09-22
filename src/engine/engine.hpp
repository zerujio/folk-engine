#ifndef FOLK_ENGINE__ENGINE_HPP
#define FOLK_ENGINE__ENGINE_HPP

#include <array>
#include <ostream>

#include "folk/scene/scene.hpp"
#include "../utils/singleton.hpp"
#include "../render/module.hpp"
#include "../audio/module.hpp"
#include "../simulation/module.hpp"
#include "engine_module.hpp"
#include "main.hpp"

namespace folk
{

// Singleton class to access aplication level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {
public:
    enum Status {OK, ERROR};

    // The engine functor is what main() calls to run the engine itself
    friend class EngineFunctor;

private:
    Scene scene {};
    int started_modules {0};
    bool exit_flag {false};

    /* Module initialization list. Modules are started up in this order, and
    shut down in reverse. */
    const std::array<EngineModule*, 3> mod_init_list {
        &SimulationModule::instance,
        &AudioModule::instance, 
        &RenderModule::instance
    };

    // start up all engine modules
    Status startUp(std::ostream&, std::ostream&) noexcept;

    // shut down all engine modules
    Status shutDown(std::ostream&, std::ostream&) noexcept;

    Status loop() noexcept;
};

#define ENGINE EngineSingleton::instance

FOLK_SINGLETON_CLASS_FINAL(EngineFunctor) {
    using Status = EngineSingleton::Status;
private:
    int operator()(std::ostream&, std::ostream&);
    static void exit() {ENGINE.exit_flag = true;}
    
    friend int ::main();
};

#define ENGINE_MAIN EngineFunctor::instance

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_HPP