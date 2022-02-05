#ifndef FOLK_CORE__ERROR_HPP
#define FOLK_CORE__ERROR_HPP

#include <string>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <utility>

#include "utils/source_location.hpp"

namespace Folk
{

/// \brief \~spanish Error del engine.
/// \brief \~english Standard engine error.
struct Error : public std::logic_error
{
    template<class What>
    explicit Error(What what, std::experimental::source_location loc = std::experimental::source_location::current())
    : std::logic_error(what), m_location(loc) {}

    [[nodiscard]]
    constexpr const auto& location() const {
        return m_location;
    }

private:
    std::experimental::source_location m_location;
};

std::ostream& operator<<(std::ostream& os, const Error& err);

/// \brief \~spanish Error crítico: lanzar una excepción de este tipo provocará la terminación del programa.
/// \brief \~english Critical error: throwing exceptions of this type will cause the engine to shut down.
struct CriticalError : public Error
{
    using Error::Error;
};

} // namespace folk

#endif//FOLK_CORE__ERROR_HPP