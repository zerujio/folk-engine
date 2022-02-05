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
#ifdef FOLK_DEBUG
struct Error : public std::logic_error
{
    explicit Error(const std::string& what, std::experimental::source_location loc = std::experimental::source_location::current())
    : std::logic_error(what), m_location(loc) {}

    explicit Error(const char* what, source_location loc = source_location::current())
    : logic_error(what), m_location(loc) {}

    [[nodiscard]]
    constexpr const auto& location() const {
        return m_location;
    }

private:
    std::experimental::source_location m_location;
};
#else
struct Error : public std::logic_error {
    using logic_error::logic_error;
};
#endif

std::ostream& operator<<(std::ostream& os, const Error& err);

/// \brief \~spanish Error crítico: lanzar una excepción de este tipo provocará la terminación del programa.
/// \brief \~english Critical error: throwing exceptions of this type will cause the engine to shut down.
struct CriticalError : public Error
{
    using Error::Error;
};

} // namespace folk

#endif//FOLK_CORE__ERROR_HPP