#include "folk/audio/audio_clip.hpp"

#include "../core/engine_singleton.hpp"

#include <dr_wav.h>
#include <dr_mp3.h>
#include <dr_flac.h>

namespace Folk
{

// 16bit PCM buffer
struct AudioBuffer final {
    unsigned int channels = 0;
    unsigned int sample_rate = 0;
    uint64_t total_pcm_frame_count = 0;

    int16_t* data;

    std::size_t size() const {
        return sizeof(int16_t) * channels * total_pcm_frame_count;
    }
};

static void checkReadErrors(std::filesystem::path& file, const AudioBuffer& buffer) {
    if (!buffer.data) {
        std::string msg = "Couldn't read file: ";
        msg += file.string();
        throw FOLK_RUNTIME_ERROR(msg);
    }
}

std::shared_ptr<AudioClip> AudioClip::createFromFile(std::filesystem::path file)
{
    AudioBuffer buffer;

    std::shared_ptr<AudioClip> ptr;

    auto ext = file.extension();

    if (ext == ".wav") {        
        buffer.data = drwav_open_file_and_read_pcm_frames_s16(
            file.c_str(),
            &buffer.channels,
            &buffer.sample_rate,
            reinterpret_cast<drwav_uint64*>(&buffer.total_pcm_frame_count),
            nullptr
        );

        checkReadErrors(file, buffer);

        ptr = std::make_shared<AudioClip>(buffer);

        drwav_free(buffer.data, nullptr);
    }
    else if (ext == ".mp3") {
        drmp3_config config;
        buffer.data = drmp3_open_file_and_read_pcm_frames_s16(
            file.c_str(),
            &config,
            reinterpret_cast<drmp3_uint64*>(&buffer.total_pcm_frame_count),
            nullptr
        );

        checkReadErrors(file, buffer);

        buffer.channels = config.channels;
        buffer.sample_rate = config.sampleRate;

        ptr = std::make_shared<AudioClip>(buffer);

        drmp3_free(buffer.data, nullptr);
    }
    else if (ext == ".flac") {
        buffer.data = drflac_open_file_and_read_pcm_frames_s16(
            file.c_str(),
            &buffer.channels,
            &buffer.sample_rate,
            reinterpret_cast<drflac_uint64*>(&buffer.total_pcm_frame_count),
            nullptr
        );

        checkReadErrors(file, buffer);

        ptr = std::make_shared<AudioClip>(buffer);

        drflac_free(buffer.data, nullptr);
    }
    else
        throw FOLK_RUNTIME_ERROR("Unsupported audio format: " 
                                 + ext.generic_string());

    return ptr;
}

AudioClip::AudioClip(const AudioBuffer& audio_buffer) 
: buffer_mngr(al::BufferManager::createId()) 
{
    ALuint format;
    if (audio_buffer.channels == 1)
        format = AL_FORMAT_MONO16;
    else if (audio_buffer.channels == 2)
        format = AL_FORMAT_STEREO16;
    else
        throw FOLK_RUNTIME_ERROR("Too many channels in audio clip");
    
    buffer_mngr.copyData(format, audio_buffer.data, audio_buffer.size(), audio_buffer.sample_rate);
    
}

AudioClip::~AudioClip() {
    auto err = buffer_mngr.destroy();
    
    try {
        if (err == AL_INVALID_OPERATION)
            throw FOLK_ERROR(al::ALError, "buffer is still in use and cannot be deleted (possible resource leak)");
        
        else if (err == AL_INVALID_NAME)
            throw FOLK_ERROR(al::ALError, "buffer id is invalid, can't delete");

        else if (err != AL_NO_ERROR)
            throw FOLK_ERROR(al::ALError, "unexpected error during buffer deletion");

    } catch (...) {
        ENGINE.exception.handle();
    }
}

} // namespace Folk
