#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <GLFW/glfw3.h>
#include "../engine/engine_module.hpp"

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(RenderModule) {
public:
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Render")

private:
    friend class RenderThread;
    class RenderThread {
    public:
        void start();
        void stop();
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
        static void staticMain();
    } render_thread;

    void onStartUp();
    void onShutDown();
};

} // namespace folk

#define RENDER RenderModule::instance

#endif//FOLK_RENDER__MODULE_HPP