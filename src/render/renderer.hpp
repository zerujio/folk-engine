#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "folk/render/shader.hpp"
#include "folk/render/mesh.hpp"

#include "../scene/scene_manager.hpp"
#include "../window/window_manager.hpp"
#include "../debug/performance_monitor.hpp"
#include "../utils/delta_clock.hpp"

#include <map>

namespace Folk {

class Renderer final {

public:
    static const char* name() {return "Renderer";}

private:
    friend class EngineSingleton;

    const WindowManager& window_mngr;

    Renderer(ExceptionHandler&, const WindowManager&);
    ~Renderer();

    void drawFrame(SceneManager& scene, std::chrono::duration<double>);

    static void drawPerfMon(const PerformanceMonitor&, DeltaClock::milliseconds_double) noexcept;
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP