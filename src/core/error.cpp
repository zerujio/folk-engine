#include "folk/error.hpp"

namespace Folk
{

std::ostream& operator<<(std::ostream& os, const Error& err) {
    os << err.location() << " : " << err.what();
    return os;
}
    
} // namespace Folk
