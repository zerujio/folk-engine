#ifndef FOLK_AUDIO__MODULE_HPP
#define FOLK_AUDIO__MODULE_HPP

#include "../utils/singleton.hpp"

#include <iostream> 

namespace Folk {

FOLK_SINGLETON_CLASS_FINAL(AudioModule) {
    friend class EngineSingleton;

    AudioModule() {
        std::cout << "Audio: initialized\n";
    }

public:
    ~AudioModule() {
        std::cout << "Audio: finalized\n";
    }
};

}

#endif