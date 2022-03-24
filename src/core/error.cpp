#include "folk/error.hpp"
#include "folk/debug.hpp"

namespace Folk
{

std::ostream& operator<<(std::ostream& os, const Error& err) {
#ifdef FOLK_DEBUG
    os << err.location() << " : " << err.what();
#else   
    os << err.what();
#endif
    return os;
}
    
} // namespace Folk
