#ifndef FOLK__ERROR_HPP
#define FOLK__ERROR_HPP

#include <stdexcept>

namespace folk
{

// Standard engine error
struct EngineRuntimeError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

// Critical error. Throwing exceptions of this type will cause the engine to shut down.
class CriticalEngineError : std::runtime_error
{
    using runtime_error::runtime_error;
};

} // namespace folk

#endif//FOLK_ENGINE__ERROR_HPP