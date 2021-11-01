#include <chrono>
#include <thread>

#include "folk/folk.hpp"

#include "engine_singleton.hpp"

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

    int delta_mon_idx = ENGINE.perf_monitor.addItem("Frame delta");
    int frame_time_idx = ENGINE.perf_monitor.addItem("Frame time");

    int mon_idx[updateable_modules.size()];
    {
        int i = 0;
        for (auto p : updateable_modules)
            mon_idx[i++] = perf_monitor.addItem(p->name());
    }

    perf_monitor.start(delta_mon_idx);
    while (!exit_flag) {
        frame_clock.click();

        Delta delta = frame_clock.delta();
        if (delta < min_frame_time) {
            std::this_thread::sleep_for(min_frame_time - delta);
            delta = min_frame_time;
        }

        perf_monitor.start(frame_time_idx);

        int i = 0;
        for (auto p : updateable_modules) {
            perf_monitor.start(mon_idx[i]);
            try {
                p->update(delta);
            } catch (...) {
                exception.handle();
            }
            perf_monitor.stop(mon_idx[i++]);
        }

        perf_monitor.stop(frame_time_idx);
        perf_monitor.stop(delta_mon_idx);

        perf_monitor.start(delta_mon_idx);
    }
}

} // namespace folk