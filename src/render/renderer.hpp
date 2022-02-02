#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "folk/math/vector.hpp"

#include "render_context.hpp"

#include "../utils/delta_clock.hpp"
#include "../utils/performance_monitor.hpp"
#include "../utils/scoped_initializer.hpp"
#include "../scene/scene_manager.hpp"

namespace Folk {

/// Manages rendering operations. Should only be called from the main thread
struct Renderer final {
    Renderer() = delete;

    /// OpenGL setup
    static void initialize();

    /// Draw a frame.
    static void drawFrame(SceneManager &scene, std::chrono::duration<double> delta);

    /// Draw the performance monitor.
    static void drawPerfMon(const PerformanceMonitor&, DeltaClock::milliseconds_double) noexcept;

    /// Set the rendering context to perform rendering operations on.
    static void setContext(RenderContextHandle);

    static void setFrameBufferSize(Vec2i size);

private:
    static RenderContextHandle s_handle;

    static bool s_frame_buffer_size_changed;
    static Vec2i s_frame_buffer_size;
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP