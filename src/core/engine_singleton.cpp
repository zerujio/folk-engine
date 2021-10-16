#include <chrono>
#include <thread>

#include "engine_singleton.hpp"
#include "folk/folk.hpp"

namespace Folk {

// EngineSingleton
EngineSingleton::EngineSingleton()
{
    // initialize engine
    try {
        engineInit();

    } catch (std::exception &e) {
        std::string msg ("engineInit exception: ");
        msg += e.what();
        throw CriticalEngineError(msg);
    
    } catch (...) {
        throw CriticalEngineError("Unexpected exception during engine initialization");
    }

    // initialize scene
    try {
        sceneInit(scene.scene);

    } catch (std::exception &e) {
        std::string msg ("sceneInit exception: ");
        msg += e.what();
        throw CriticalEngineError(msg);

    } catch (...) {
        throw CriticalEngineError("Unexpected exception during scene initialization");
    }
}

EngineSingleton::~EngineSingleton()
{
    
}

void EngineSingleton::exit() noexcept
{
    exit_flag = true;
}

void EngineSingleton::mainLoop()
{
    using Delta = UpdateListener::Delta;

    while (!exit_flag) {
        frame_clock.click();

        Delta delta = frame_clock.delta();
        if (delta < min_frame_time) {
            std::this_thread::sleep_for(min_frame_time - delta);
            delta = min_frame_time;
        }
        
        for (auto p : updateable_modules) {
            try {
                p->update(delta);
            } catch (...) {
                exception.handle();
            }
        }
    }
}

} // namespace folk