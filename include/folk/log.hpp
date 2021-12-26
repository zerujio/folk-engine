#ifndef FOLK_CORE__LOG_HPP
#define FOLK_CORE__LOG_HPP

#include <mutex>
#include <iostream>

namespace Folk
{
    enum class LogLevel {
        Trace, Message, Warning, Error
    };

    std::ostream& operator<<(std::ostream& out, LogLevel level);

    /// Object that manages concurrent write access to an std::ostream.
    /**
     * The mutex associated with the stream is locked when the object is constructed and remains in that state for the
     * lifetime of the object.
     */
    class ConcurrentStreamWriter final {
        std::ostream* m_out {nullptr};
        std::unique_lock<std::mutex> m_lk {};

    public:
        /// Null message. Does not write to any stream or lock any mutex.
        ConcurrentStreamWriter() = default;

        /**
         * @brief Construct object that locks mutex and writes to given stream.
         * Mutex is released when LogMessage is destroyed.
         *
         * @param out stream to write to.
         * @param lk unique_lock to use for the lifetime of the object. Will be std::move d from.
         */
        ConcurrentStreamWriter(std::ostream &out, std::unique_lock<std::mutex> &lk) : m_out(&out), m_lk(std::move(lk)) {}

        /// Write to underlying stream using operator<<.
        /**
         * It is valid to call this on a null message. The function will have no effect.
         * @tparam T type of argument
         * @param x object to write out. An implementation of operator<<(std::ostream&, T&) must exist.
         * @return This LogMessage.
         */
        template<class T>
        ConcurrentStreamWriter& operator<<(T&& x) {
            if (m_out and m_lk)
                *m_out << x;
            return *this;
        }
    };

    struct LogData;

    class Log final {
        static LogLevel s_level;    // LogLevel
        static LogData* s_data;     // dynamically allocated data (i.e. buffers)
        static std::mutex s_mutex;

        friend class LogThread;
        friend class LogInitializer;

    public:
        /// Begin writing a message to the log with the given LogLevel.
        static ConcurrentStreamWriter write(LogLevel level);

        static auto trace() { return write(LogLevel::Trace); }
        static auto message() { return write(LogLevel::Message); }
        static auto warning() { return write(LogLevel::Warning); }
        static auto error() { return write(LogLevel::Error); }
    };

} // namespace Folk



#endif // FOLK_CORE__LOG_HPP