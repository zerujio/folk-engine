#ifndef FOLK_ENGINE__ERROR_HPP
#define FOLK_ENGINE__ERROR_HPP

#include <stdexcept>

namespace folk
{

struct EngineRuntimeError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

} // namespace folk

#endif//FOLK_ENGINE__ERROR_HPP