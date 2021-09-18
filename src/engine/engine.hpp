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

    using EngineErrorList = std::list<EngineRuntimeError>;

    enum Status {SUCCESS, FAILURE};

    friend class Manager;
    /* Engine class for controlled access to engine startup/shutdown methods.
      Only friends of the Manager class can access these methods.

      Startup/shutdown methods are only meant to be used by whomever intializes
      the engine, so they can't be public. This manager allows the main() to
      access private methods, without also giving access to all other internal
      Engine member functions and variables.
    */
    class Manager final {
    public:
        Manager() = default;
        Manager(const Manager&) = delete;
        Manager& operator=(const Manager&) = delete;

    private:
        // start up all engine modules
        Status startUp(std::ostream&);

        // shut down engine modules
        Status shutDown(std::ostream&);

        Status setScene(Scene* s);

        // grant main access to the engine manager
        friend int ::main();
    };

    //~EngineSingleton();

    Manager manager {};

    Scene& scene() {return *scene_ptr;};

private:
    Scene* scene_ptr {nullptr};
    int started_modules {0};

    /* Module initialization list. Modules are started up in this order, and
    shut down in reverse. */
    const std::array<EngineModule*, 3> mod_init_list 
        {&AudioModule::instance, 
        &RenderModule::instance, 
        &SimulationModule::instance};

    // start up all engine modules
    void startUp();

    // shut down all engine modules
    void shutDown();

    // set current scene
    void setScene(Scene*);
    
};

#define ENGINE EngineSingleton::instance

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_HPP