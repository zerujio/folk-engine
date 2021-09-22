#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "../engine/engine_module.hpp"

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(RenderModule) {
    void onStartUp() {}
    void onShutDown() {}
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Render")
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP