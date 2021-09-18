#include <list>
#include <string>

#include "engine.hpp"

namespace folk {

void EngineSingleton::startUp() 
{
    while (started_modules < mod_init_list.size()) {
        mod_init_list[started_modules]->startUp();
        ++started_modules;
    }
}

void EngineSingleton::shutDown()
{
    EngineErrorList errors;

    while (started_modules > 0) {
        try {
            mod_init_list[--started_modules]->shutDown();
        } catch (EngineRuntimeError &e) {
            errors.push_back(e);
        }
    }

    if (!errors.empty())
        throw errors;
}

void EngineSingleton::setScene(Scene* scn) {
    scene_ptr = scn;
}

EngineSingleton::Status EngineSingleton::Manager::startUp(std::ostream& out) {
    try {
        ENGINE.startUp();
    }

    catch (EngineRuntimeError &e) {
        out << "Startup error: " << e.what() << "\n";
        shutDown(out);
        return FAILURE;
    }

    return SUCCESS;
}

EngineSingleton::Status EngineSingleton::Manager::shutDown(std::ostream& out) {
    try {
        ENGINE.shutDown();   
    }

    catch (EngineErrorList &elist) {
        out << "During shutdown the following errors ocurred:\n";
        for (auto& err : elist) {
            out << err.what() << "\n";
        }
        return FAILURE;
    }

    return SUCCESS;
}

EngineSingleton::Status EngineSingleton::Manager::setScene(Scene* scn) {
    try {
        ENGINE.setScene(scn);
    } catch(...) {
        return FAILURE;
    }
    return SUCCESS;
}

} // namespace folk