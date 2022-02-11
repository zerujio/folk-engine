#ifndef FOLK_CORE__LOG_HPP
#define FOLK_CORE__LOG_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <sstream>

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

    template<class C> class ScopedInitializer;

    struct Log {

        Log() = delete;

        /// Begin writing a message to the log with the given LogLevel.
        static ConcurrentStreamWriter write(LogLevel level);

        static auto trace() { return write(LogLevel::Trace); }
        static auto message() { return write(LogLevel::Message); }
        static auto warning() { return write(LogLevel::Warning); }
        static auto error() { return write(LogLevel::Error); }

    private:

        friend class ScopedInitializer<Log>;

        struct Buffer {
            std::stringstream stream {};
            std::mutex mutex {};
        };

        static void initialize(LogLevel level, Log::Buffer& out_buf, Log::Buffer& err_buf);
        static void terminate() noexcept;

        static void main();
        static void printBuffer(Buffer& buffer, std::ostream& out);

        static LogLevel s_level;
        static std::thread s_thread;
        static std::mutex s_mutex;
        static std::condition_variable s_condition;
        static bool s_terminate_flag;
        static bool s_wake_up_flag;
        static Buffer* s_out_buf_ptr;
        static Buffer* s_err_buf_ptr;
    };

    template<>
    struct ScopedInitializer<Log> {

        ScopedInitializer(LogLevel level);
        ~ScopedInitializer() noexcept;

        ScopedInitializer(const ScopedInitializer&) = delete;
        ScopedInitializer& operator=(const ScopedInitializer&) = delete;

        void wakeUp() const;

    private:
        Log::Buffer out_buf {};
        Log::Buffer err_buf {};
    };

} // namespace Folk



#endif // FOLK_CORE__LOG_HPP