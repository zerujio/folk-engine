#ifndef FOLK_AUDIO__AUDIO_CLIP_HPP
#define FOLK_AUDIO__AUDIO_CLIP_HPP

#include "folk/core/resource.hpp"
#include "folk/audio/open_al.hpp"

#include <filesystem>

namespace Folk {

struct AudioBuffer;

class AudioClip : public Resource {
    friend class AudioSourcePtr;
    
    al::BufferManager buffer_mngr;

public:
    AudioClip(AudioBuffer const&);
    ~AudioClip();

    /// Crea un clip a partir de un archivo (mp3, wav o flac).
    static std::shared_ptr<AudioClip> createFromFile(std::filesystem::path);
};

} // namespace Folk

#endif // FOLK_AUDIO__AUDIO_CLIP_HPP