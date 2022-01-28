#ifndef FOLK_AUDIO__AUDIO_MANAGER_HPP
#define FOLK_AUDIO__AUDIO_MANAGER_HPP

#include "folk/audio/audio_source_component.hpp"

#include "../scene/scene_manager.hpp"
#include "folk/core/exception_handler.hpp"

#include "alc.hpp"

#include <entt/entt.hpp>

#include <iostream> 

namespace Folk {

class AudioManager final {

    alc::DeviceManager m_device;
    alc::ContextManager m_context {m_device};

     static void updateListener(const ExceptionHandler&, SceneManager&, std::chrono::duration<double>) noexcept;
     static void updateSource(const ExceptionHandler &exception_handler, SceneGraphNode &node_component,
                       const AudioSourceComponent &source_component, std::chrono::duration<float> delta) noexcept;

public:
    static const char* name() {return "AudioManager";}

    explicit AudioManager(const ExceptionHandler&);

    void update(const ExceptionHandler&, SceneManager&, std::chrono::duration<double>) const noexcept;
};

}

#endif // FOLK_AUDIO__AUDIO_MANAGER_HPP