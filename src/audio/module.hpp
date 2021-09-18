#ifndef FOLK_AUDIO__MODULE_HPP
#define FOLK_AUDIO__MODULE_HPP

#include "../engine/engine_module.hpp"

#include <iostream>

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(AudioModule) {
    void onStartUp() {std::cout << "Audio module up!\n";}
    void onShutDown() {std::cout << "Audio module down!\n";}
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Audio")
};

}

#endif