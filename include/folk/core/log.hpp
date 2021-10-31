#ifndef FOLK_CORE__LOG_HPP
#define FOLK_CORE__LOG_HPP

#include <mutex>
#include <iostream>

namespace Folk
{

enum class LogLevel {
    NONE, ERROR, WARNING, MESSAGE, TRACE
};

class LogMessage {
    std::ostream& out;
    std::unique_lock<std::mutex> lk;
public:
    LogMessage(std::ostream& o, std::mutex& m) : out(o), lk(m) {}
    LogMessage(std::ostream& o) : out(o) {}

    template<class T>
    LogMessage& operator<<(T const& x) {
        if (lk)
            out << x;

        return *this;
    }
};

LogMessage log(LogLevel);

} // namespace Folk



#endif // FOLK_CORE__LOG_HPP