#ifndef FOLK_CORE__ERROR_HPP
#define FOLK_CORE__ERROR_HPP

#include <stdexcept>

namespace Folk
{

/// Standard engine error.
struct EngineRuntimeError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

/// Critical error: throwing exceptions of this type will cause the engine to shut down.
class CriticalEngineError : public std::runtime_error
{
    using runtime_error::runtime_error;
};

} // namespace folk

#endif//FOLK_CORE__ERROR_HPP