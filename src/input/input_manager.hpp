#ifndef FOLK_INPUT__INPUT_MANAGER
#define FOLK_INPUT__INPUT_MANAGER

#include "folk/input/input.hpp"
#include "../utils/singleton.hpp"
#include "../core/exception_handler.hpp"

#include <GLFW/glfw3.h>

#include <map>
#include <string>

namespace Folk
{

struct InputActionProxy {
    InputAction action {};
};

#define INPUT InputManager::instance()

FOLK_SINGLETON_CLASS_FINAL(InputManager) {

public:
    const char* name() const {return "Input Manager";}

    InputManager(ExceptionHandler&);
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

    friend Cursor::CallbackId Cursor::addCallback(Cursor::CallbackType&&);
    friend void Cursor::removeCallback(Cursor::CallbackId const);

    friend Scroll::CallbackId Scroll::addCallback(Scroll::CallbackType&&);
    friend void Scroll::removeCallback(Scroll::CallbackId const);

private:
    IdIntType next_id {0};

    template <class T>
    T genId() {
        return static_cast<T>(next_id++);
    }

    // user defined callbacks 
    std::map<Key_CallbackId, Key_CallbackType> key_callbacks_;
    std::map<MouseButton_CallbackId, MouseButton_CallbackType> mouse_btn_callbacks_;
    std::map<InputCode_CallbackId, InputCode_CallbackType> input_code_callbacks_;
    std::map<Cursor::CallbackId, Cursor::CallbackType> cursor_callbacks_;
    std::map<Scroll::CallbackId, Scroll::CallbackType> scroll_callbacks_;

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

#endif // FOLK_INPUT__INPUT_MANAGER