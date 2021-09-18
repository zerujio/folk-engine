#include <iostream>
#include <thread>
#include <list>
#include <chrono>
#include <csignal>

// include
#include "folk/folk.hpp"
#include "folk/engine/error.hpp"
#include "engine.hpp"
#include "main.hpp"

static bool should_close = false;

void signalHandler(int sig) {
    should_close = true;
}

void setSignalHandler() {
    struct sigaction new_action, old_action;
    new_action.sa_handler = signalHandler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    for (auto signal : {SIGINT, SIGHUP, SIGTERM}) {
        sigaction(signal, nullptr, &old_action);
        if (old_action.sa_handler != SIG_IGN)
            sigaction(signal, &new_action, nullptr);
    }
}

int main() {
    setSignalHandler();

    using Status = folk::EngineSingleton::Status;

    folk::Scene scene;
    folk::ENGINE.manager.setScene(&scene);

    // start engine modules
    if (folk::ENGINE.manager.startUp(std::cerr) != Status::SUCCESS)
        return -1;

    // initialize scene
    try {
        folk::sceneInit(scene);

    } catch (std::exception &e) {
        std::cerr << "Error during scene initialization: " << e.what() << "\n";
        folk::ENGINE.manager.shutDown(std::cerr);
        return -1;
    
    } catch (...) {
        std::cerr << "Unexpected exception during scene initialization!\n";
        folk::ENGINE.manager.shutDown(std::cerr);
        return -1;
    }

    // loop
    while(not should_close) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // shutdown
    if (folk::ENGINE.manager.shutDown(std::cerr) != Status::SUCCESS)
        return -1;

    return 0;
}
