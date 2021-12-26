#include "folk/log.hpp"
#include "folk/error.hpp"

#include "log_thread.hpp"
#include "engine_singleton.hpp"

namespace Folk
{

    LogLevel Log::s_level {LogLevel::Warning};
    LogData* Log::s_data {nullptr};
    std::mutex Log::s_mutex {};

    std::ostream& operator<<(std::ostream& os, LogLevel level) {
        const char* str;

        switch (level)
        {
        case LogLevel::Trace:
            str = "TRACE";
            break;

        case LogLevel::Message:
            str = "MESSAGE";
            break;

        case LogLevel::Warning:
            str = "WARNING";
            break;

        case LogLevel::Error:
            str = "ERROR";
            break;

        default:
            str = "NONE";
            break;
        }

        return os << str;
    }

ConcurrentStreamWriter Log::write(LogLevel lvl)
{
    std::scoped_lock lock {s_mutex};

    if (!Log::s_data)
        throw FOLK_RUNTIME_ERROR("Log has not been initialized");

    if (lvl >= s_level) {
        LogData::Buffer &buffer = (lvl <= LogLevel::Message) ? Log::s_data->out : Log::s_data->err_out;

        std::unique_lock buffer_lock {buffer.mutex};
        buffer.stream << "[" << lvl << "] ";

        return {buffer.stream, buffer_lock};
    }
    else
        // default constructor = input is ignored.
        return {};
}

} // namespace Folk
