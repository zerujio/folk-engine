#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "folk/render/shader.hpp"
#include "folk/render/mesh.hpp"

#include "../core/module.hpp"

#include "../debug/log.hpp"
#include "../core/exception_handler.hpp"

#include <bgfx/bgfx.h>

#include <map>

namespace Folk {

struct BGFXCallbackHandler final : public bgfx::CallbackI {

    BGFXCallbackHandler(Log&, ExceptionHandler&);

    void fatal(const char* file_path, uint16_t line, 
               bgfx::Fatal::Enum code, const char* description) override;
    
    void traceVargs(const char* file_path, uint16_t line,
                    const char* format, va_list arg_list) override;
    
    void profilerBegin(const char* name, uint32_t abgr_color, 
                       const char* file_path, uint16_t line) override
    {}

    void profilerBeginLiteral(const char* name, uint32_t abgr_color,
                              const char* file_path, uint16_t line) override
    {}

    void profilerEnd() override
    {}

    uint32_t cacheReadSize(uint64_t id) override {
        return 0;
    }

    bool cacheRead(uint64_t id, void* data, uint32_t size) override {
        return false;
    }

    void cacheWrite(uint64_t id, const void* data, uint32_t size) override {
    }

    void screenShot(const char* file_path, uint32_t width, uint32_t height,
                    uint32_t pitch, const void* data, uint32_t size, bool yflip) override;

    void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, 
                     bgfx::TextureFormat::Enum _format, bool _yflip) override;

    void captureEnd() override;

    void captureFrame(const void *_data, uint32_t _size) override;

private:
    Log& m_log;
    ExceptionHandler& m_handler;
};

FOLK_ENGINE_UPDATEABLE_MODULE(Renderer){
public:
    const char* name() const override {return "Renderer";}

private:
    friend class EngineSingleton;

    int perf_monitor_id;

    const bgfx::ViewId view_id {0};

    BGFXCallbackHandler bgfx_callback_handler;

    Renderer(Log&, ExceptionHandler&);
    ~Renderer();

    void update(Delta) override;

    void imguiDraw();
};

} // namespace folk

#define RENDER Renderer::instance()

#endif//FOLK_RENDER__MODULE_HPP