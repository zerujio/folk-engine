#ifndef FOLK_AUDIO__AUDIO_SOURCE_COMPONENT_HPP
#define FOLK_AUDIO__AUDIO_SOURCE_COMPONENT_HPP

#include "folk/scene/component_ptr.hpp"
#include "folk/audio/audio_clip.hpp"
#include "folk/audio/al_source.hpp"

#include <memory>

namespace Folk
{

class AudioSourcePtr;

struct AudioSourceComponent final {
    using ptr_type = AudioSourcePtr;
    static constexpr const char* type_name = "AudioSource";

    std::shared_ptr<AudioClip> audio_clip {};
    al::SourceManager source_manager {};
};

struct AudioSourcePtr final : public ComponentPtr<AudioSourceComponent> {

    using ComponentPtr::ComponentPtr;

    /// Puntero al AudioClip en uso
    [[nodiscard]] std::shared_ptr<AudioClip> getAudioClip() const;

    /// Configura el clip de audio a reproducir
    void setAudioClip(std::shared_ptr<AudioClip> audio_clip) const;

    /// Consulta si esta fuente está configurada para repetirse.
    [[nodiscard]] bool getLooping() const;

    /// Configura esta fuente para repetir el clip de audio.
    void setLooping(bool) const;

    /// Inicia la reproducción de audio
    void play() const;

    /// Pausa la reproducción de audio
    void pause() const;

    /// Detiene la reproducción de audio
    void stop() const;

    /// Reinicia la fuente. 
    void rewind() const;
};

} // namespace Folk


#endif // FOLK_AUDIO__AUDIO_SOURCE_COMPONENT_HPP