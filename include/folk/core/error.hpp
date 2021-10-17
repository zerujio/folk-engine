#ifndef FOLK_CORE__ERROR_HPP
#define FOLK_CORE__ERROR_HPP

#include <stdexcept>

namespace Folk
{

/// \brief \~spanish Error del engine.
/// \brief \~english Standard engine error.
struct EngineRuntimeError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

/// \brief \~spanish Error crítico: lanzar una excepción de este tipo provocará la terminación del programa.
/// \brief \~english Critical error: throwing exceptions of this type will cause the engine to shut down.
class CriticalEngineError : public std::runtime_error
{
    using runtime_error::runtime_error;
};

} // namespace folk

#endif//FOLK_CORE__ERROR_HPP