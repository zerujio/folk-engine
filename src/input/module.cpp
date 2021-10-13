#include "folk/input/input.hpp"

#include "../core/engine_singleton.hpp"

#include "module.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Folk
{

KeyState getKey(Key key) {
    return static_cast<KeyState>(glfwGetKey(ENGINE.window.getWindowPtr(), key));
}

KeyState InputAction::state() {
    for (auto key : keys)
        if (glfwGetKey(ENGINE.window.getWindowPtr(), key) == GLFW_PRESS) {
            return keystate_press;
        }
    
    return keystate_release;
}

} // namespace folk
