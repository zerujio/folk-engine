#include "folk/log.hpp"
#include "folk/error.hpp"

#include "main.hpp"
#include "engine_singleton.hpp"

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

Folk::LogLevel parseLevel(std::string const& str) {

    std::string upper {str};

    for (auto& c : upper)
        c = toupper(c);

    if (upper == "ERROR")
        return Folk::LogLevel::Error;

    else if (upper == "WARNING")
        return Folk::LogLevel::Warning;

    else if (upper == "MESSAGE")
        return Folk::LogLevel::Message;

    else if (upper == "TRACE")
        return Folk::LogLevel::Trace;

    else
        throw FOLK_ERROR(Folk::RuntimeError, "can't parse log level: " + str);
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
        
        std::cout << "LogLevel: " << loglevel << "\n";

        Folk::EngineSingleton engine {loglevel};
        engine.mainLoop();

    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
        return -1;
    }

    return 0;
}
