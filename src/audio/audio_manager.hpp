#ifndef FOLK_AUDIO__AUDIO_MANAGER_HPP
#define FOLK_AUDIO__AUDIO_MANAGER_HPP

#include "../core/module.hpp"

#include "open_alc.hpp"

#include <entt/entt.hpp>

#include <iostream> 

namespace Folk {

FOLK_ENGINE_MODULE(AudioManager) {

    alc::DeviceManager m_device;
    alc::ContextManager m_context {m_device};

public:
    const char* name() const {return "AudioManager";}

    AudioManager();

    void connectRegistry(entt::registry&);
};

}

#endif // FOLK_AUDIO__AUDIO_MANAGER_HPP