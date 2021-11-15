#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "folk/render/shader.hpp"
#include "folk/render/mesh.hpp"

#include "../core/module.hpp"

#include "shader_data.hpp"

#include <bgfx/bgfx.h>

#include <map>

namespace Folk {

FOLK_ENGINE_UPDATEABLE_MODULE(Renderer){
public:
    const char* name() const override {return "Renderer";}

private:
    friend class EngineSingleton;

    int perf_monitor_id;

    const bgfx::ViewId view_id {0};

    float view_mat[16];
    float proj_mat[16];

    Renderer();
    ~Renderer();

    void update(Delta) override;

    void imguiDraw();
};

} // namespace folk

#define RENDER Renderer::instance()

#endif//FOLK_RENDER__MODULE_HPP