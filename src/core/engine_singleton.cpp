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
        exception.handleException();
        throw std::runtime_error("engineInit() error");
    }

    // initialize scene
    try {
        sceneInit(scene.scene);

    } catch (...) {
        exception.handleException();
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

void EngineSingleton::mainLoop() noexcept
{
    while (!exit_flag) {
        frame_clock.click();
 
        auto delta = frame_clock.delta();
        if (delta < min_frame_time) {
            auto ti = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(min_frame_time - delta);
            delta += std::chrono::steady_clock::now() - ti;
        }

        update(delta);
    }
}

void EngineSingleton::update(std::chrono::nanoseconds delta) {
    // start frame
    auto frame_time_id = perf_monitor.addItem("Frame time");

    // update window / process input
    {
        auto monitor_id = perf_monitor.addItem("Input processing");
        window.update();
        perf_monitor.stop(monitor_id);
    }

    // update scene
    {
        auto id = perf_monitor.addItem("Scene update");
        try {
            scene.updateScene(delta);
        } catch (...) {
            log.begin(LogLevel::WARNING)
                << "An error ocurred during scene update phase:\n";
            exception.handleException();
        }
        perf_monitor.stop(id);
    }

    // update audio
    {
        auto id = perf_monitor.addItem("Audio update");
        try {
            audio.update(scene, delta);
        } catch (...) {
            log.begin(LogLevel::WARNING) 
                << "An error ocurred during audio processing phase:\n";
            exception.handleException();
        }
        perf_monitor.stop(id);
    }

    // draw
    {
        auto id = perf_monitor.addItem("Renderer");
        try {
            render.drawFrame(scene, delta);
        } catch (...) {
            log.begin(LogLevel::WARNING)
                << "An error ocurred during draw phase:\n";
            exception.handleException();
        }
        perf_monitor.stop(id);
    }

    // end frame
    perf_monitor.stop(frame_time_id);

    // draw performance metrics
    render.drawPerfMon(perf_monitor, delta);
    perf_monitor.clear();
}

} // namespace folk