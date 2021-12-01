#ifndef FOLK_AUDIO__AUDIO_MANAGER_HPP
#define FOLK_AUDIO__AUDIO_MANAGER_HPP

#include "../core/module.hpp"

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream> 

namespace Folk {

FOLK_ENGINE_MODULE(AudioManager) {

    ALCdevice* device {nullptr};

public:
    const char* name() const {return "audio";}

    AudioManager() {
        // empty
    }

    ~AudioManager() {
        // empty
    }
};

}

#endif // FOLK_AUDIO__AUDIO_MANAGER_HPP