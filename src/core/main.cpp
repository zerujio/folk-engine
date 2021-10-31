// include
#include "folk/folk.hpp"
#include "folk/core/error.hpp"
#include "engine_singleton.hpp"
#include "main.hpp"

#include <cxxopts.hpp>

#include <iostream>
#include <thread>
#include <list>
#include <chrono>

#include <csignal>
#include <cctype>

void signalHandler(int sig) {
    Folk::ENGINE.exit();
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

Folk::Log::Level parseLevel(std::string const& str) {

    std::string upper {str};

    for (auto& c : upper) {
        c = toupper(c);
    }

    if (upper == "NONE")
        return Folk::Log::Level::NONE;

    else if (upper == "ERROR")
        return Folk::Log::Level::ERROR;

    else if (upper == "WARNING")
        return Folk::Log::Level::WARNING;

    else if (upper == "MESSAGE")
        return Folk::Log::Level::MESSAGE;

    else if (upper == "TRACE")
        return Folk::Log::Level::TRACE;

    else
        throw Folk::EngineRuntimeError("can't parse log level: " + str);
}

int main(int argc, char** argv) {
    setSignalHandler();

    cxxopts::Options options("FolkEngine Game", "Run FolkEngine game.");

    options.add_options()
        ("l,loglevel", "Set logging level to one of NONE|ERROR|WARNING|MESSAGE|TRACE.",
         cxxopts::value<std::string>()->default_value("WARNING"));

    try {
        auto result = options.parse(argc, argv);
        auto loglevel = parseLevel(result["loglevel"].as<std::string>());

        Folk::EngineSingleton engine {};
        engine.log.setLevel(loglevel);

        engine.mainLoop();

    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
        return -1;
    }

    return 0;
}
