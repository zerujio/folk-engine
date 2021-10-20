#ifndef FOLK_INPUT__UTILS_HPP
#define FOLK_INPUT__UTILS_HPP

#include "folk/input/input.hpp"

namespace Folk
{

constexpr int intCast(Key key) {
    return static_cast<int>(key);
}

constexpr int intCast(MouseButton mb) {
    return static_cast<int>(mb) - 1;
}

constexpr Key keyCast(int glfw_code) {
    return static_cast<Key>(glfw_code);
}

constexpr MouseButton mouseButtonCast(int glfw_code) {
    return static_cast<MouseButton>(glfw_code + 1);
}

constexpr InputState stateCast(int glfw_state) {
    return static_cast<InputState>(glfw_state);
}

} // namespace Folk


#endif // FOLK_INPUT__UTILS_HPP