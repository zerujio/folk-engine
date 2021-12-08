#ifndef FOLK_AUDIO__AUDIO_MANAGER_HPP
#define FOLK_AUDIO__AUDIO_MANAGER_HPP

#include "folk/audio/audio_source_component.hpp"

#include "../scene/scene_manager.hpp"

#include "open_alc.hpp"

#include <entt/entt.hpp>

#include <iostream> 

namespace Folk {

class AudioManager final {

    alc::DeviceManager m_device;
    alc::ContextManager m_context {m_device};

     void updateListener(SceneManager&, std::chrono::duration<double>) const noexcept;
     void updateSource(SceneGraphNode &node_component, const AudioSourceComponent &source_component, std::chrono::duration<double> delta) const noexcept;

public:
    static const char* name() {return "AudioManager";}

    AudioManager();

    static void connectRegistry(entt::registry&);

    void update(SceneManager&, std::chrono::duration<double>) const noexcept;
};

}

#endif // FOLK_AUDIO__AUDIO_MANAGER_HPP