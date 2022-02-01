#ifndef FOLK_INPUT__UTILS_HPP
#define FOLK_INPUT__UTILS_HPP

#include "key.hpp"
#include "mouse_button.hpp"
#include "input_code.hpp"

namespace Folk
{

constexpr int intCast(const Key key) {
    return static_cast<int>(key);
}

constexpr int intCast(const MouseButton mb) {
    return static_cast<int>(mb);
}

constexpr Key keyCast(const int glfw_code) {
    return static_cast<Key>(glfw_code);
}

constexpr MouseButton mouseButtonCast(const int glfw_code) {
    return static_cast<MouseButton>(glfw_code);
}

constexpr InputState stateCast(const int glfw_state) {
    return static_cast<InputState>(glfw_state);
}

} // namespace Folk


#endif // FOLK_INPUT__UTILS_HPP