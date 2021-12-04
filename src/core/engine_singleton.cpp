#include <chrono>
#include <thread>

#include "folk/folk.hpp"

#include "engine_singleton.hpp"

namespace Folk {

// EngineSingleton
EngineSingleton::EngineSingleton(Log::Level log_level)
    : log(log_level)
{
    // initialize engine
    try {
        audio.connectRegistry(scene.registry());
        engineInit();

    } catch (...) {
        exception.handle();
        throw std::runtime_error("engineInit() error");
    }

    // initialize scene
    try {
        sceneInit(scene.scene);

    } catch (...) {
        exception.handle();
        throw std::runtime_error("sceneInit() error");
    }
}

EngineSingleton::~EngineSingleton()
try {
    // empty
} catch (RuntimeError &e) {
    std::cerr << "Engine shutdown error: " << e << "\n";
} catch (std::exception &e) {
    std::cerr << "Engine shutdown error: " << e.what() << "\n"; 
} catch (...) {
    std::cerr << "Unknown engine shutdown exception.\n"; 
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