#include "folk/core/error.hpp"

namespace Folk
{

std::ostream& operator<<(std::ostream& os, const RuntimeError& err) {
    os << err.file() << ":" 
       << err.line() << " ( " 
       << err.function() << " ) : "
       << err.what();
    
    return os;
}
    
} // namespace Folk
