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

EngineSingleton::~EngineSingleton()
{
    exception_queue.stopProcessing();
}

void EngineSingleton::exit() noexcept
{
    exit_flag = true;
}

void EngineSingleton::transportException(std::exception_ptr p) noexcept
{
    exception_queue.enqueue(p);
}

void EngineSingleton::mainLoop()
{
    std::vector<UpdateListener*> to_update {&window, &render};
    while (!exit_flag) {
        for (UpdateListener* p : to_update)
            try {
                p->update(0.16);
            } catch (...) {
                transportException(std::current_exception());
            }
    }
}

void EngineSingleton::handleException(std::exception_ptr ptr) noexcept
{
    try {
        if (ptr)
            std::rethrow_exception(ptr);
    } catch (CriticalEngineError &e) {
        errout << "Critical error: " << e.what() << "\n";
        exit();
    } catch (std::exception &e) {
        errout << "Error: " << e.what() << "\n";
    } catch (...) {
        errout << "Critical error: caught unexpected exception!\n";
        exit();
    }
}

} // namespace folk