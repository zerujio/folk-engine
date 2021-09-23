#ifndef FOLK_THREAD__MANAGER_THREAD_HPP
#define FOLK_THREAD__MANAGER_THREAD_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <exception>
#include "folk/error.hpp"

namespace folk {

enum ThreadStatus {RUNNING, NOT_RUNNING, ERROR};

class ThreadedModule {
    friend class ManagerThread;
private:
    virtual void threadStartUp() = 0;
    virtual void threadUpdate() = 0;
    virtual void threadShutDown() = 0;
};

class ManagerThread final
{
public:
    ManagerThread(ThreadedModule &mod) : _module(mod) {};
    ManagerThread(ManagerThread const&) = delete;
    ManagerThread& operator=(ManagerThread const&) = delete;

    /* Calls the startUp function. If start up succeeds, the update function is
    called until the thread is stopped.*/
    void start();

    /* Signals the thread to stop and waits for it to be joined. */
    void stop();

    ThreadStatus status() {return _status;}

private:
    ThreadedModule &_module;
    ThreadStatus _status {NOT_RUNNING};
    bool _stop_flag {false};
    std::exception_ptr p_exception {};
    // threading things
    std::thread thread {};
    std::mutex mutex {};
    std::condition_variable condition {};

    bool shouldStop();
    void setStatus(ThreadStatus);
    void main();
};

} // namespace folk

#endif//FOLK_THREAD__MANAGER_THREAD_HPP
