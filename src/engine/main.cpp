#include <iostream>
#include <thread>
#include <list>
#include <chrono>
#include <csignal>

// include
#include "folk/folk.hpp"
#include "folk/error.hpp"
#include "engine_singleton.hpp"
#include "main.hpp"

void signalHandler(int sig) {
    folk::ENGINE.exit();
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

    try {
        folk::EngineSingleton engine {};
        engine.mainLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
