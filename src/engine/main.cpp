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

using callbackType = void (*)();
static callbackType exitCallback;

void signalHandler(int sig) {
    exitCallback();
}

void setSignalHandler(callbackType f) {
    exitCallback = f;
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
    setSignalHandler(folk::ENGINE_MAIN.exit);
    return folk::ENGINE_MAIN(std::cout, std::cerr);
}
