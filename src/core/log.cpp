#include "folk/log.hpp"
#include "folk/error.hpp"

namespace Folk {

LogLevel Log::s_level {LogLevel::Warning};
std::thread Log::s_thread {};
std::mutex Log::s_mutex {};
std::condition_variable Log::s_condition {};
bool Log::s_terminate_flag {false};
bool Log::s_wake_up_flag {false};
Log::Buffer* Log::s_out_buf_ptr {nullptr};
Log::Buffer* Log::s_err_buf_ptr {nullptr};

ScopedInitializer<Log>::ScopedInitializer() {
    Log::initialize(out_buf, err_buf);
}

ScopedInitializer<Log>::~ScopedInitializer() noexcept {
    Log::terminate();
}

void ScopedInitializer<Log>::wakeUp() {
    if (Log::s_wake_up_flag)
        Log::s_condition.notify_all();
}

void Log::initialize(Log::Buffer &out_buf, Log::Buffer &err_buf) {
    if (s_out_buf_ptr || s_err_buf_ptr)
        throw CriticalError("Log initialized twice");

    std::scoped_lock lk {s_mutex};
    s_out_buf_ptr = &out_buf;
    s_err_buf_ptr = &err_buf;
    s_thread = std::thread(Log::main);
}

void Log::terminate() noexcept
try
{
    if (!s_out_buf_ptr || !s_out_buf_ptr) {
        std::cerr << "Log::terminate(): log has not been initialized." << std::endl;
        return;
    }

    {
        std::scoped_lock lk{s_mutex};
        s_terminate_flag = true;
        s_wake_up_flag = true;
    }

    s_condition.notify_all();
    s_thread.join();
}
catch (std::exception& e)
{
    std::cerr << "Log::terminate(): an error ocurred: " << e.what() << std::endl;
    return;
}

void Log::main() {
    std::unique_lock lk {s_mutex};

    if (!s_out_buf_ptr or !s_err_buf_ptr) {
        std::cerr << "[Error] Log was not properly initialized. Log thread has been shut down.";
        return;
    }

    while (!s_terminate_flag) {
        s_condition.wait(lk, [](){ return s_wake_up_flag; });

        printBuffer(*s_out_buf_ptr, std::cout);
        printBuffer(*s_err_buf_ptr, std::cerr);

        s_wake_up_flag = false;
    }

    s_terminate_flag = false;
}

void Log::printBuffer(Buffer &buffer, std::ostream &out) {
    std::scoped_lock lock {buffer.mutex};

    // if stream is not empty...
    if (buffer.stream.peek() != decltype(buffer.stream)::traits_type::eof()) {

        out << buffer.stream.rdbuf();

        if (!out.good()) {
            bool out_bad = out.bad();
            bool out_fail = out.fail();
            bool out_eof = out.eof();

            bool buf_bad = buffer.stream.bad();
            bool buf_fail = buffer.stream.fail();
            bool buf_eof = buffer.stream.eof();

            out.clear();

            out << "Output error [fail|bad|eof]\n"
                   "buffer : " << buf_fail << buf_bad << buf_eof << "\n" <<
                "out    : " << out_fail << out_bad << out_eof << "\n";
        }
    }
}

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

    if (!s_out_buf_ptr or !s_err_buf_ptr)
        throw Error("Log has not been initialized");

    if (lvl >= s_level) {
        Log::Buffer &buffer = (lvl <= LogLevel::Message) ? *s_out_buf_ptr : *s_err_buf_ptr;

        std::unique_lock buffer_lock {buffer.mutex};
        buffer.stream << "[" << lvl << "] ";

        s_wake_up_flag = true;

        return {buffer.stream, buffer_lock};
    }
    else
        // default constructor = input is ignored.
        return {};
}

} // namespace Folk
