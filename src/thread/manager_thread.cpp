#include "folk/error.hpp"
#include "manager_thread.hpp"
#include "../engine/engine_singleton.hpp"

namespace folk {

ThreadStatus ManagerThread::status() 
{
    return _status;
}

void ManagerThread::setStatus(ThreadStatus s) 
{
    std::lock_guard lock(mutex);
    _status = s;
}

void ManagerThread::start() 
{
    {
        std::unique_lock lock(mutex);
        thread = std::thread(ManagerThread::main, this);

        while (_status == NOT_RUNNING)
            condition.wait(lock);
    }

    if (_status == ERROR) {
        thread.join();
        std::rethrow_exception(p_exception);
    }
}

void ManagerThread::stop()
{
    {
        std::lock_guard lg(mutex);
        _stop_flag = true;
    }

    thread.join();
    _stop_flag = false;

    if (_status == ERROR) {
        std::rethrow_exception(p_exception);
    }
}

void ManagerThread::main()
{
    try {
        _module.threadStartUp();
    } catch(...) {
        p_exception = std::current_exception();
        setStatus(ERROR);
        condition.notify_all();
        return;
    }

    setStatus(RUNNING);
    condition.notify_all();
    
    while (not shouldStop())
    {
        try {
            _module.threadUpdate();
        } catch (...) {
            ENGINE.transportException(std::current_exception());
        }
    }

    try {
        _module.threadShutDown();
    } catch (...) {
        p_exception = std::current_exception();
        setStatus(ERROR);
        return;
    }

    setStatus(NOT_RUNNING);
}

} // namespace folk