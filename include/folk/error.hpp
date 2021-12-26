#ifndef FOLK_CORE__ERROR_HPP
#define FOLK_CORE__ERROR_HPP

#include <string>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <utility>

namespace Folk
{

/// \brief \~spanish Error del engine.
/// \brief \~english Standard engine error.
struct RuntimeError : public std::exception
{
    /**
     * @brief Construct a new Runtime Error object
     * 
     * @param what_ string descriptivo.
     * @param file_ archivo en que sucedió el error (macro __FILE__).
     * @param line_ línea del archivo en que sucedió el error (macro __LINE__).
     * @param function_ función en que sucedió el error (macro __func__/__PRETTY_FUNCTION__). 
     */
    RuntimeError(const char* what_, 
                 const char* file_, 
                 const unsigned int line_, 
                 const char* function_)
    : what_string(what_), m_file(file_), m_line(line_), m_function(function_)
    {
        // empty
    }

    RuntimeError(std::string what_, const char* file_,
                 const unsigned int line_, const char* function_)
    : what_string(std::move(what_)), m_file(file_), m_line(line_), m_function(function_)
    {
        // empty
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return what_string.c_str();
    }

    [[nodiscard]] const char* file() const noexcept {
        return m_file;
    }

    [[nodiscard]] unsigned int line() const noexcept {
        return m_line;
    }

    [[nodiscard]] const char* function() const noexcept {
        return m_function;
    }

private:
    const std::string what_string;
    const char* m_file;
    const unsigned int m_line;
    const char* m_function;
};

std::ostream& operator<<(std::ostream& os, const RuntimeError& err);

/// \brief \~spanish Error crítico: lanzar una excepción de este tipo provocará la terminación del programa.
/// \brief \~english Critical error: throwing exceptions of this type will cause the engine to shut down.
struct CriticalError : public RuntimeError
{
    using RuntimeError::RuntimeError;
};

#define FOLK_HERE_ARGS __FILE__, __LINE__, __PRETTY_FUNCTION__

#define FOLK_ERROR(ExceptionClass, what) ExceptionClass(what, FOLK_HERE_ARGS)

#define FOLK_RUNTIME_ERROR(what) FOLK_ERROR(RuntimeError, what)

#define FOLK_CRITICAL_ERROR(what) FOLK_ERROR(CriticalError, what)

} // namespace folk

#endif//FOLK_CORE__ERROR_HPP