#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "../engine/engine_module.hpp"

#include <iostream>

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(RenderModule) {
    void onStartUp() {std::cout << "Render module up!\n";}
    void onShutDown() {std::cout << "Render module down!\n";}
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Render")
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP