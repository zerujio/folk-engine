#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <GLFW/glfw3.h>
#include "../utils/singleton.hpp"

namespace folk {

FOLK_SINGLETON_CLASS_FINAL(RenderModule) {
private:
    friend class EngineSingleton;
    friend class RenderThread;

    class RenderThread {
    public:
        RenderThread();
        ~RenderThread();

    private:
        enum Status {STARTED, STOPPED, ERROR} status {STOPPED};
        std::thread thread;
        std::mutex mutex;
        std::condition_variable condition;
        bool stop_flag {false};

        void main();
        bool configureContext();
        void renderLoop();
        bool checkStopFlag();
    } render_thread;

    RenderModule() {}
    ~RenderModule() {}
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP