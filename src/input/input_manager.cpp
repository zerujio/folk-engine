#include "folk/input/input.hpp"

#include "../core/engine_singleton.hpp"

#include "input_manager.hpp"
#include "utils.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Folk
{

void keyCallback(GLFWwindow*, int, int, int, int);
void mouseButtonCallback(GLFWwindow*, int, int, int);

InputManager::InputManager() {
    glfwSetKeyCallback(ENGINE.window.getWindowPtr(), keyCallback);
    glfwSetMouseButtonCallback(ENGINE.window.getWindowPtr(), mouseButtonCallback);
}

InputManager::~InputManager() {
    glfwSetKeyCallback(ENGINE.window.getWindowPtr(), nullptr);
    glfwSetMouseButtonCallback(ENGINE.window.getWindowPtr(), nullptr);
}

void keyCallback(GLFWwindow* window, int keycode, int scancode, int action, 
                int mods) 
{
    if (action == GLFW_REPEAT)
        return;

    auto key = keyCast(keycode);
    auto state = stateCast(action);

    if (keycode != GLFW_KEY_UNKNOWN) {
        for (auto& p : INPUT.key_callbacks) {
            p.second(key, state);
        }
        INPUT.inputCallback(key, state);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
    if (action == GLFW_REPEAT)
        return;

    auto btn = mouseButtonCast(button);
    auto state = stateCast(action);

    for (auto& p : INPUT.mouse_btn_callbacks)
        p.second(btn, state);

    INPUT.inputCallback(mouseButtonCast(button), stateCast(action));
}

void InputManager::inputCallback(InputCode code, InputState state) {
    for (auto& p : INPUT.input_code_callbacks)
        p.second(code, state);

    for (InputAction::Binding* binding : input_bindings_[code]) {
        auto old_state = binding->state();

        for (int i = 0; i < 4; ++i)
            if (binding->combination_[i] == code) {
                binding->state_[i] = state;
                break;
            }
        
        auto new_state = binding->state();

        if (old_state != new_state) {
            for (auto &callback : binding->action_->callbacks_)
                callback.second(new_state);
        }
    }
}

} // namespace folk
