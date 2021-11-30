#include <AL/al.h>
#include <AL/alc.h>

#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

#include <type_traits>
#include <iostream>
#include <string>
#include <vector>

#include <cstdint>


// Tomado de: 
// https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
bool check_al_errors(const std::string& filename, const std::uint_fast32_t line)
{
    ALenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n" ;
        switch(error)
        {
        case AL_INVALID_NAME:
            std::cerr << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";
            break;
        case AL_INVALID_ENUM:
            std::cerr << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
            break;
        case AL_INVALID_VALUE:
            std::cerr << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";
            break;
        case AL_INVALID_OPERATION:
            std::cerr << "AL_INVALID_OPERATION: the requested operation is not valid";
            break;
        case AL_OUT_OF_MEMORY:
            std::cerr << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory";
            break;
        default:
            std::cerr << "UNKNOWN AL ERROR: " << error;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}

template<typename alFunction, typename... Params>
auto alCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alFunction function,
    Params... params)
    -> typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, decltype(function(params...))>
{
    auto ret = function(std::forward<Params>(params)...);
    check_al_errors(filename, line);
    return ret;
}

template<typename alFunction, typename... Params>
auto alCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alFunction function,
    Params... params)
    ->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
{
    function(std::forward<Params>(params)...);
    return check_al_errors(filename, line);
}

#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)


bool check_alc_errors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
{
    ALCenum error = alcGetError(device);
    if(error != ALC_NO_ERROR)
    {
        std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n" ;
        switch(error)
        {
        case ALC_INVALID_VALUE:
            std::cerr << "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function";
            break;
        case ALC_INVALID_DEVICE:
            std::cerr << "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function";
            break;
        case ALC_INVALID_CONTEXT:
            std::cerr << "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function";
            break;
        case ALC_INVALID_ENUM:
            std::cerr << "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function";
            break;
        case ALC_OUT_OF_MEMORY:
            std::cerr << "ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function";
            break;
        default:
            std::cerr << "UNKNOWN ALC ERROR: " << error;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}

template<typename alcFunction, typename... Params>
auto alcCallImpl(const char* filename, 
                 const std::uint_fast32_t line, 
                 alcFunction function, 
                 ALCdevice* device, 
                 Params... params)
->typename std::enable_if_t<std::is_same_v<void,decltype(function(params...))>, bool>
{
    function(std::forward<Params>(params)...);
    return check_alc_errors(filename,line,device);
}

template<typename alcFunction, typename ReturnType, typename... Params>
auto alcCallImpl(const char* filename,
                 const std::uint_fast32_t line,
                 alcFunction function,
                 ReturnType& returnValue,
                 ALCdevice* device,
                 Params... params)
->typename std::enable_if_t<!std::is_same_v<void,decltype(function(params...))>, bool>
{
    returnValue = function(std::forward<Params>(params)...);
    return check_alc_errors(filename,line,device);
}

#define alcCall(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)


struct WavData {
    unsigned int channels = 0;
    unsigned int sample_rate = 0;
    drwav_uint64 total_PCM_frame_count = 0;
    drwav_int16* pcm_data {nullptr};

    drwav_uint64 totalSamples() const {
        return total_PCM_frame_count * channels;
    }

    ~WavData() {
        if (pcm_data)
            drwav_free(pcm_data, nullptr);
    }
};

int main(int argc, const char* argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <filename>\n";
        return -1;
    }

    WavData audio_data;

    audio_data.pcm_data = drwav_open_file_and_read_pcm_frames_s16(
        argv[1],
        &audio_data.channels,
        &audio_data.sample_rate,
        &audio_data.total_PCM_frame_count,
        nullptr
    );

    if (!audio_data.pcm_data) {
        std::cerr << "Couldn't open file \n";
        return -1;
    }

    float total_time = (float) audio_data.total_PCM_frame_count 
                     / (float) audio_data.sample_rate;

    // dispositivo predeterminado

    ALCdevice* device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Couldn't open audio device\n";
        return -1;
    }

    // crear contexto
    ALCcontext* context;
    if(!alcCall(alcCreateContext, context, device, device, nullptr) || !context)
    {
        std::cerr << "ERROR: Could not create audio context" << std::endl;
        return -1;
    }

    // makeCurrent
    ALCboolean made_current;
    if (!alcCall(alcMakeContextCurrent, made_current, device, context)
        || made_current != ALC_TRUE)
    {
        std::cerr << "Couldn't make audio context current\n";
    }

    // BUFFER
    ALenum format;
    if (audio_data.channels == 1) {
        format = AL_FORMAT_MONO16;
    } else if (audio_data.channels == 2) {
        format = AL_FORMAT_STEREO16;
    } else {
        std::cerr << "unknown audio format!";
        return -1;
    }

    ALuint buffer;
    alCall(alGenBuffers, 1, &buffer);
    alCall(alBufferData, buffer, 
                         format, 
                         audio_data.pcm_data, 
                         audio_data.totalSamples() * sizeof(drwav_int16),
                         audio_data.sample_rate);

    ALuint source;
    alCall(alGenSources, 1, &source);
    alCall(alSourcef, source, AL_PITCH, 1);
    alCall(alSourcef, source, AL_GAIN, 1.0f);
    alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
    alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
    alCall(alSourcei, source, AL_LOOPING, AL_FALSE);
    alCall(alSourcei, source, AL_BUFFER, buffer);

    alCall(alSourcePlay, source);

    ALint state;
    do {
        alCall(alGetSourcei, source, AL_SOURCE_STATE, &state);
    } while ( state == AL_PLAYING );

    alCall(alDeleteSources, 1, &source);
    alCall(alDeleteBuffers, 1, &buffer);

    // destroy context
    alcCall(alcMakeContextCurrent, made_current, device, nullptr);
    if (!alcCall(alcDestroyContext, device, context) && context) {
        std::cerr << "Couldn't destroy current context\n";
    }

    // close
    ALCboolean closed;
    if (!alcCall(alcCloseDevice, closed, device, device)) {
        std::cerr << "Could not close device.\n";
        return -1;
    }

    return 0;
}
