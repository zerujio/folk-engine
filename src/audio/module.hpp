#ifndef FOLK_AUDIO__MODULE_HPP
#define FOLK_AUDIO__MODULE_HPP

#include "../core/module.hpp"

#include <iostream> 

namespace Folk {

FOLK_ENGINE_MODULE(AudioModule) {
    friend class EngineSingleton;

    const char* name() const {return "audio";}

    AudioModule() {
        // empty
    }

public:
    ~AudioModule() {
        // empty
    }
};

}

#endif