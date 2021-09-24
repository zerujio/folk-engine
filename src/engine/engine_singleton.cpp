#include <chrono>
#include <thread>

#include "engine_singleton.hpp"
#include "folk/folk.hpp"

namespace folk {

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
        sceneInit(scene);

    } catch (std::exception &e) {
        std::string msg ("sceneInit exception: ");
        msg += e.what();
        throw CriticalEngineError(msg);

    } catch (...) {
        throw CriticalEngineError("Unexpected exception during scene initialization");
    }
}

EngineSingleton::~EngineSingleton() {}

void EngineSingleton::exit() noexcept
{
    exit_flag = true;
}

void EngineSingleton::mainLoop() noexcept
{
    // wait until exit call
    while (not exit_flag) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

} // namespace folk