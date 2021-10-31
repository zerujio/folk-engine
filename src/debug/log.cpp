#include "log.hpp"

#include "folk/core/error.hpp"
#include "../core/engine_singleton.hpp"

namespace Folk
{

std::ostream& operator<<(std::ostream& os, Log::Level level) {
    const char* str;

    switch (level)
    {
    case Log::Level::TRACE:
        str = "TRACE";
        break;

    case Log::Level::MESSAGE:
        str = "MESSAGE";
        break;

    case Log::Level::WARNING:
        str = "WARNING";
        break;
    
    case Log::Level::ERROR:
        str = "ERROR";
        break;
    
    default:
        str = "NONE";
        break;
    }

    return os << str;
}

void Log::setLevel(Log::Level lvl) {
    std::lock_guard lk {mutex};
    log_level = lvl;
}

Log::Level Log::getLevel() {
    std::lock_guard lk {mutex};
    return log_level;
}

LogMessage Log::begin(Log::Level lvl) {
    if (lvl == Log::Level::NONE)
        throw EngineRuntimeError("NONE is not a valid level for a message");

    else if (lvl <= log_level) {
        out << "[" << lvl << "] ";
        return LogMessage(out, mutex);
    }
    else
        // no mutex = input is ignored.
        return LogMessage(out);
}

LogMessage log(Log::Level lvl) {
    return ENGINE.log.begin(lvl);
}

} // namespace Folk
