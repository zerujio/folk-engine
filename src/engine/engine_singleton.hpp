#ifndef FOLK_ENGINE__ENGINE_SINGLETON_HPP
#define FOLK_ENGINE__ENGINE_SINGLETON_HPP

#include <array>
#include <ostream>
#include <iostream>
#include <exception>
#include <thread>

#include "folk/scene.hpp"
#include "../utils/singleton.hpp"
#include "../render/module.hpp"
#include "../audio/module.hpp"
#include "../simulation/module.hpp"
#include "../window/module.hpp"
#include "../utils/processing_queue.hpp"
#include "../utils/coroutine.hpp"
#include "main.hpp"

namespace folk
{

// Singleton class to access aplication level functions and variables.
FOLK_SINGLETON_CLASS_FINAL(EngineSingleton) {

public:
    // Engine modules
    WindowModule window {};
    RenderModule render {};
    AudioModule audio {};
    SimulationModule simulation {};

    // signal the engine to exit
    void exit() noexcept;

    /* Transport an exception across threads, from the calling thread to the
    handler thread. The exception is thrown again in said thread and then 
    handled.*/
    void transportException(std::exception_ptr) noexcept;

    std::ostream& out {std::cout};
    std::ostream& errout {std::cerr}; 

private:
    EngineSingleton();
    ~EngineSingleton();

    void mainLoop();
    void handleException(std::exception_ptr) noexcept;

    bool exit_flag {false};
    Scene scene {};
    ProcessingQueue<std::exception_ptr> exception_queue;
    Coroutine exception_handler {
        &ProcessingQueue<std::exception_ptr>::processLoop,
        &exception_queue,
        [this](std::exception_ptr p){ handleException(p); }
    };

    friend int ::main();
};

#define ENGINE EngineSingleton::instance()

} // namespace folk

#endif//FOLK_ENGINE__ENGINE_SINGLETON_HPP