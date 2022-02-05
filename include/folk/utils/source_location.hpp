//
// Created by sergio on 04-02-22.
//

#ifndef INCLUDE_FOLK_UTILS__SOURCE_LOCATION_HPP
#define INCLUDE_FOLK_UTILS__SOURCE_LOCATION_HPP

#include <experimental/source_location>
#include <iostream>

namespace Folk {

using std::experimental::source_location;

std::ostream &operator<<(std::ostream &out, source_location loc);

} // namespace Folk

#endif //INCLUDE_FOLK_UTILS__SOURCE_LOCATION_HPP
