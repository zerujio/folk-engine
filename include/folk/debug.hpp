//
// Created by sergio on 03-02-22.
//

#ifndef INCLUDE_FOLK__DEBUG_HPP
#define INCLUDE_FOLK__DEBUG_HPP

namespace Folk {

#ifdef FOLK_DEBUG
constexpr bool c_debug_build {true};
#else
constexpr bool c_debug_build {false};
#endif

}

#endif //INCLUDE_FOLK__DEBUG_HPP
