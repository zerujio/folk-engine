//
// Created by sergio on 26-12-21.
//

#include "log_thread.hpp"

namespace Folk {

    /*  LogInitializer */

    LogInitializer::LogInitializer() {
        std::scoped_lock lock {Log::s_mutex};

        if (Log::s_data)
            throw FOLK_RUNTIME_ERROR("Log has already been initialized");

        Log::s_data = &m_data;
    }

    LogInitializer::~LogInitializer() {
        std::scoped_lock lock {Log::s_mutex};
        Log::s_data = nullptr;
    }


    /* LogThread */

    LogThread::LogThread() {
        if (!Log::s_data) {
            joinThread();
            throw FOLK_RUNTIME_ERROR("Log has not been initialized");
        }
    }

    LogThread::~LogThread() {
        joinThread();
    }

    void LogThread::wakeUp() {
        m_wake_up_flag = true;
        m_condition.notify_all();
    }

    void LogThread::joinThread() {
        m_destructor_flag = true;
        wakeUp();
        m_thread.join();
    }

    void LogThread::printBuffer(LogData::Buffer &buffer, std::ostream &out) {
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

    void LogThread::main() {
        std::unique_lock lk {m_mutex};

        while (!m_destructor_flag) {
            m_condition.wait(lk, [this](){ return m_wake_up_flag; });

            std::scoped_lock log_lock {Log::s_mutex};
            if (!Log::s_data) {
                std::cout << "[Error] Log data pointer is null: log thread has been shut down.";
                break;
            }

            printBuffer(Log::s_data->out, std::cout);
            printBuffer(Log::s_data->err_out, std::cerr);
        }
    }

} // namespace Folk