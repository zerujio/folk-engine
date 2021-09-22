#ifndef FOLK_AUDIO__MODULE_HPP
#define FOLK_AUDIO__MODULE_HPP

#include "../engine/engine_module.hpp"

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(AudioModule) {
    void onStartUp() {}
    void onShutDown() {}
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Audio")
};

}

#endif