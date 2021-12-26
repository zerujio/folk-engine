//
// Created by sergio on 26-12-21.
//

#ifndef SRC_CORE__LOG_THREAD_HPP
#define SRC_CORE__LOG_THREAD_HPP

#include "folk/log.hpp"
#include "folk/error.hpp"

#include <mutex>
#include <thread>
#include <condition_variable>
#include <sstream>

namespace Folk {

    /// Contains the log's dynamically allocated data.
    struct LogData final {

        struct Buffer {
            std::stringstream stream;
            std::mutex mutex;
        };

        Buffer out {};
        Buffer err_out {};
    };

    /// Initializes/finalizes the Log.
    class LogInitializer final {
        LogData m_data {};

    public:
        LogInitializer();
        ~LogInitializer();
    };

    // Manages a LogThread.
    class LogThread final {
        std::thread m_thread {&LogThread::main, this};
        std::mutex m_mutex {};
        std::condition_variable m_condition {};
        bool m_destructor_flag {false};
        bool m_wake_up_flag {false};

        void main();
        void joinThread();
        static void printBuffer(LogData::Buffer&, std::ostream&);

    public:

        LogThread();
        ~LogThread();

        void wakeUp();
    };
}

#endif //SRC_CORE__LOG_THREAD_HPP
