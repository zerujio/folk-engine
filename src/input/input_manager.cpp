#include "folk/input/input.hpp"

#include "../core/engine_singleton.hpp"

#include "input_manager.hpp"
#include "utils.hpp"

#include <GLFW/glfw3.h>

namespace Folk
{

void keyCallback(GLFWwindow*, int, int, int, int);
void mouseButtonCallback(GLFWwindow*, int, int, int);

InputManager::InputManager() {
    glfwSetKeyCallback(ENGINE.window.windowPtr(), keyCallback);
    glfwSetMouseButtonCallback(ENGINE.window.windowPtr(), mouseButtonCallback);
}

InputManager::~InputManager() {
    glfwSetKeyCallback(ENGINE.window.windowPtr(), nullptr);
    glfwSetMouseButtonCallback(ENGINE.window.windowPtr(), nullptr);
}

void keyCallback(GLFWwindow* window, int keycode, int scancode, int action, 
                int mods) 
{
    if (action == GLFW_REPEAT)
        return;

    if (keycode != GLFW_KEY_UNKNOWN) {
        auto key = keyCast(keycode);
        auto state = stateCast(action);

        for (auto& p : INPUT.key_callbacks_) {
            try {
                p.second(key, state);
            } catch (...) {
                ENGINE.exception.handle();
            }
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

    for (auto& p : INPUT.mouse_btn_callbacks_) {
        try {
            p.second(btn, state);
        } catch (...) {
            ENGINE.exception.handle();
        }
    }

    INPUT.inputCallback(btn, state);
}

void InputManager::inputCallback(InputCode code, InputState state) {
    for (auto& p : INPUT.input_code_callbacks_) {
        try {
            p.second(code, state);
        } catch (...) {
            ENGINE.exception.handle();
        }
    }

    auto [begin, end] = bindings_.equal_range(code);

    for (auto iter = begin; iter != end; ++iter) {
        for (auto& [_, f] : iter->second->callbacks_) {
            try {
                f(state);
            } catch (...) {
                ENGINE.exception.handle();
            }
        }
    }
}

} // namespace folk
