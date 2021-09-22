#include <chrono>
#include <thread>

#include "engine_singleton.hpp"
#include "folk/folk.hpp"

namespace folk {

// EngineSingleton

EngineSingleton::Status EngineSingleton::loop() noexcept
{
    try {
        while (not exit_flag) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } catch (...) {
        return ERROR;
    }
    return OK;
}

void EngineSingleton::exit() noexcept
{
    exit_flag = true;
}

EngineSingleton::Status EngineSingleton::startUp(std::ostream& std_out, 
        std::ostream& err_out) noexcept
{
    std_out << "Starting up...\n";

    while (started_modules < mod_init_list.size()) {
        auto& mod = *mod_init_list[started_modules];

        std_out << "> " << mod.name() << " : ";

        try {
            mod.startUp();
        } catch (std::exception &e) {
            std_out << "ERROR\n";
            err_out << mod.name() << ": start up error: " << e.what() << "\n";
            return ERROR;
        } catch (...) {
            std_out << "ERROR\n";
            return ERROR;
        }

        std_out << "OK\n";

        ++started_modules;
    }

    return OK;
}

EngineSingleton::Status EngineSingleton::shutDown(std::ostream& std_out, 
        std::ostream& err_out) noexcept
{
    std_out << "Shutting down...\n";

    while (started_modules > 0) {
        auto& mod = *mod_init_list[--started_modules];

        std_out << "> " << mod.name() << " : "; 

        try {
            mod.shutDown();
        } catch (std::exception &e) {
            std_out << "ERROR\n";
            err_out << mod.name() << ": shut down error: " << e.what() << "\n";
            return ERROR;
        } catch (...) {
            std_out << "ERROR\n";
            return ERROR;
        }

        std_out << "OK\n";
    }

    return OK;
}


// Engine Functor
int EngineFunctor::operator() (std::ostream& std_out, std::ostream& err_out) 
{
    // module startup
    if (ENGINE.startUp(std_out, err_out) != Status::OK) {
        ENGINE.shutDown(std_out, err_out);
        return 1;
    }

    // scene initialization
    bool init_ok = true;
    try {
        sceneInit(ENGINE.scene);
    } catch (std::exception &e) {
        err_out << "Exception caught during scene initialization: " 
            << e.what() << "\n";
        init_ok = false;
    } catch (...) {
        err_out << "Unknown exception caught during scene initialization!\n";
        init_ok = false;
    }

    if (not init_ok) {
        std_out << "Scene initialization failed.\n";
        ENGINE.shutDown(std_out, err_out);
        return 1;
    }

    // loop
    auto loop_status = ENGINE.loop();

    // shutdown
    auto shut_down_status = ENGINE.shutDown(std_out, err_out);

    return loop_status == Status::OK && shut_down_status == Status::OK ? 0 : 1;
}

} // namespace folk