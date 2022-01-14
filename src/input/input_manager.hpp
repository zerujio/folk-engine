#ifndef FOLK_INPUT__INPUT_MANAGER
#define FOLK_INPUT__INPUT_MANAGER

#include "folk/input.hpp"
#include "../utils/singleton.hpp"
#include "folk/core/exception_handler.hpp"
#include "../window/window_manager.hpp"

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

    GLFWwindow * m_window_ptr;

public:
    static const char* name() { return "Input Manager"; }

    explicit InputManager(ExceptionHandler&, const WindowManager&);
    ~InputManager();

    [[nodiscard]] InputState pollKey(Key) const;
    [[nodiscard]] InputState pollMouseButton(MouseButton) const;

    friend Key_CallbackId addKeyCallback(Key_CallbackType&&);
    friend MouseButton_CallbackId addMouseButtonCallback(MouseButton_CallbackType&&);
    friend InputCode_CallbackId addInputCodeCallback(InputCode_CallbackType&&);

    friend void removeKeyCallback(Key_CallbackId);
    friend void removeMouseButtonCallback(MouseButton_CallbackId);
    friend void removeInputCodeCallback(InputCode_CallbackId);

    friend InputAction& InputAction::create(std::string const&);
    friend InputAction& InputAction::get(std::string const&);
    friend void InputAction::destroy(std::string const&);

    friend void InputAction::bind(InputCode);
    friend void InputAction::unbind(InputCode);

    friend Cursor::CallbackId Cursor::addCallback(Cursor::CallbackType&&);
    friend void Cursor::removeCallback(Cursor::CallbackId);

    friend Scroll::CallbackId Scroll::addCallback(Scroll::CallbackType&&);
    friend void Scroll::removeCallback(Scroll::CallbackId);
};

} // namespace folk

#endif // FOLK_INPUT__INPUT_MANAGER