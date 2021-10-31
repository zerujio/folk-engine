#ifndef FOLK_DEBUG__LOG_HPP
#define FOLK_DEBUG__LOG_HPP

#include "folk/core/log.hpp"

namespace Folk
{

class Log {
public:
    using Level = LogLevel;

    Log() {}
    Log(std::ostream& os_) : out(os_) {}
    Log(std::ostream& os_, Log::Level lvl_) : out(os_), log_level(lvl_) {}
    Log(Log::Level lvl_) : log_level(lvl_) {}

    Log(Log const&) = delete;
    Log& operator=(Log const&) = delete;

    void setLevel(Log::Level lvl);
    Log::Level getLevel();

    LogMessage begin(Log::Level lvl);

private:
    std::ostream& out {std::cout};
    std::mutex mutex;
    Log::Level log_level {Log::Level::WARNING};
};

std::ostream& operator<<(std::ostream& out, Log::Level level);

} // namespace Folk


#endif // FOLK_DEBUG__LOG_HPP