#ifndef FOLK_AUDIO__AUDIO_ERROR_HPP
#define FOLK_AUDIO__AUDIO_ERROR_HPP

#include "folk/core/error.hpp"

namespace Folk {

struct OpenALError : public EngineRuntimeError {
    using EngineRuntimeError::EngineRuntimeError;
};

}

#endif // FOLK_AUDIO__AUDIO_ERROR_HPP