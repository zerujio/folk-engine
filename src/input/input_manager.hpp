#ifndef FOLK_INPUT__INPUT_MANAGER
#define FOLK_INPUT__INPUT_MANAGER

#include "folk/input/input.hpp"

#include "../core/module.hpp"

#include <GLFW/glfw3.h>

#include <set>
#include <map>

namespace Folk
{

FOLK_ENGINE_MODULE(InputManager) {

public:
    const char* name() const override {return "Input manager";}

    InputManager();
    ~InputManager();

    std::map<CallbackId, KeyCallbackT> key_callbacks;
    std::map<CallbackId, MouseButtonCallbackT> mouse_btn_callbacks;
    std::map<CallbackId, InputCodeCallbackT> input_code_callbacks;

private:
    void inputCallback(InputCode, InputState);

    std::map<InputCode, std::set<InputAction::Binding*>> input_bindings_ {};

    friend class InputAction::Binding;

    friend void keyCallback(GLFWwindow*, int, int, int, int);
    friend void mouseButtonCallback(GLFWwindow*, int, int, int);
};

} // namespace folk

#define INPUT InputManager::instance()

#endif // FOLK_INPUT__INPUT_MANAGER