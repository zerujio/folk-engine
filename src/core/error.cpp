#include "folk/error.hpp"
#include "folk/debug.hpp"

namespace Folk
{

std::ostream& operator<<(std::ostream& os, const Error& err) {
    if constexpr(c_debug_build)
        os << err.location() << " : " << err.what();
    else
        os << err.what();
    return os;
}
    
} // namespace Folk
