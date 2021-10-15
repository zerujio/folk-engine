#include "folk/input/input.hpp"

#include "../core/engine_singleton.hpp"

#include "module.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Folk
{

KeyState getKey(Key key) {
    return static_cast<KeyState>(glfwGetKey(ENGINE.window.getWindowPtr(), 
                                 static_cast<int>(key)));
}

KeyState InputAction::state() {
    for (auto key : keys)
        if (glfwGetKey(ENGINE.window.getWindowPtr(), static_cast<int>(key)) 
            == GLFW_PRESS) {
            return KeyState::Press;
        }
    
    return KeyState::Release;
}

} // namespace folk
