#ifndef FOLK_INPUT__INPUT_MANAGER
#define FOLK_INPUT__INPUT_MANAGER

#include "folk/input/input.hpp"

#include "../core/module.hpp"

#include <GLFW/glfw3.h>

#include <map>
#include <string>

namespace Folk
{

struct InputActionProxy {
    InputAction action {};
};

FOLK_ENGINE_MODULE(InputManager) {

public:
    const char* name() const override {return "Input Manager";}

    InputManager();
    ~InputManager();

    friend Key_CallbackId addKeyCallback(Key_CallbackType&&);
    friend MouseButton_CallbackId addMouseButtonCallback(MouseButton_CallbackType&&);
    friend InputCode_CallbackId addInputCodeCallback(InputCode_CallbackType&&);

    friend void removeKeyCallback(Key_CallbackId const);
    friend void removeMouseButtonCallback(MouseButton_CallbackId const);
    friend void removeInputCodeCallback(InputCode_CallbackId const);

    friend InputAction& InputAction::create(std::string const&);
    friend InputAction& InputAction::get(std::string const&);
    friend void InputAction::destroy(std::string const&);

    friend void InputAction::bind(InputCode const);
    friend void InputAction::unbind(InputCode const);

private:
    static IdIntType next_id;

    // user defined callbacks 
    std::map<IdIntType, Key_CallbackType> key_callbacks_;
    std::map<IdIntType, MouseButton_CallbackType> mouse_btn_callbacks_;
    std::map<IdIntType, InputCode_CallbackType> input_code_callbacks_;

    // InputAction
    std::map<std::string, InputActionProxy> actions_;
    std::multimap<InputCode, InputAction*> bindings_;

    // callback dispatcher
    void inputCallback(InputCode, InputState);

    // glfw callbacks
    friend void keyCallback(GLFWwindow*, int, int, int, int);
    friend void mouseButtonCallback(GLFWwindow*, int, int, int);
};

} // namespace folk

#define INPUT InputManager::instance()

#endif // FOLK_INPUT__INPUT_MANAGER