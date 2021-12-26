#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "folk/render/shader.hpp"
#include "folk/render/mesh.hpp"

#include "../scene/scene_manager.hpp"
#include "../window/window_manager.hpp"
#include "../debug/performance_monitor.hpp"
#include "../utils/delta_clock.hpp"

#include "bgfx_callback_handler.hpp"

#include <bgfx/bgfx.h>

#include <map>

namespace Folk {

class Renderer final {

public:
    static const char* name() {return "Renderer";}

private:
    friend class EngineSingleton;

    const bgfx::ViewId view_id {0};

    BGFXCallbackHandler bgfx_callback_handler;
    WindowManager& window_mngr;

    Renderer(ExceptionHandler&, WindowManager&);
    ~Renderer();

    void drawFrame(SceneManager& scene,
                   std::chrono::duration<double>);

    static void drawPerfMon(const PerformanceMonitor&, DeltaClock::milliseconds_double) noexcept;
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP