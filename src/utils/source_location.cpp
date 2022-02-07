//
// Created by sergio on 04-02-22.
//

#include "folk/utils/source_location.hpp"

namespace Folk {

std::ostream &operator<<(std::ostream &out, source_location loc) {
    out << loc.file_name()
        << " (" << loc.line() << ":" << loc.column() << ") "
        << loc.function_name();
    return out;
}

} // namespace Folk