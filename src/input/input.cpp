#include "folk/input.hpp"
#include "input_initializer.hpp"

#include "input_manager.hpp"
#include "input_event_queue.hpp"

#include "GLFW/glfw3.h"

namespace Folk {

InputManager g_input_manager;
InputEventQueue* g_input_queue;

template<class InputType>
void inputCallback(InputType code, InputState state) {
    g_input_queue->enqueue(code, state);
}

Input::ScopedInitializer::ScopedInitializer(InputManager input_manager, InputEventQueue &input_queue)
{
    g_input_manager = InputManager(input_manager);
    g_input_queue = &input_queue;

    g_input_manager.setKeyCallback<inputCallback>();
    g_input_manager.setMouseButtonCallback<inputCallback>();
}

Input::ScopedInitializer::~ScopedInitializer() {
    g_input_manager.clearKeyCallback();
    g_input_manager.clearMouseButtonCallback();
}

InputState Input::get(const Key key) {
    return g_input_manager.getKey(key);
}

InputState Input::get(const MouseButton mb) {
    return g_input_manager.getMouseButton(mb);
}

InputState Input::get(const InputCode code) {
    if (code.isKey())
        return g_input_manager.getKey(Key(code));
    else
        return g_input_manager.getMouseButton(MouseButton(code));
}

InputState Input::get(const InputAction& action) {

    for (auto code : action.bindings().data()) {
        if (Input::get(code) == InputState::Press)
            return InputState::Press;
    }

    return InputState::Release;
}

const char* Input::getKeyName(Key key) {
    if (key == Key::Space)
        return "Space";
    
    else if (intCast(key) < 256)
        return glfwGetKeyName(intCast(key), 0);
    
    else {
        const char *invalid = "<código inválido>";
        const char * key_names[93] = {
            "Escape",   // 256
            "Enter",
            "Tab",
            "Backspace",
            "Insert",
            "Delete",
            "Right",
            "Left",
            "Down",
            "Up",
            "PageUp",
            "PageDown",
            "Home",
            "End",      // 269
            invalid, invalid, invalid, invalid, invalid, //274
            invalid, invalid, invalid, invalid, invalid, //279
            "CapsLock", //280
            "ScrollLock",   
            "NumLock",
            "PrintScreen",
            "Pause",    // 284
            invalid,    // 285
            invalid,    // 286
            invalid,    // 287
            invalid,    // 288
            invalid,    // 289
            "F1",       // 290
            "F2",
            "F3",
            "F4",
            "F5",
            "F6",
            "F7",
            "F8",
            "F9",
            "F10",
            "F11",
            "F12",
            "F13",
            "F14",
            "F15",
            "F16",
            "F17",
            "F18",
            "F19",
            "F20",
            "F21",
            "F22",
            "F23",
            "F24",
            "F25",  // 314
            invalid,// 315
            invalid,// 316
            invalid,// 317
            invalid,// 318
            invalid,// 319
            "KeyPad0",  // 320
            "KeyPad1",
            "KeyPad2",
            "KeyPad3",
            "KeyPad4",
            "KeyPad5",
            "KeyPad6",
            "KeyPad7",
            "KeyPad8",
            "KeyPad9",
            "KeyPadDecimal",
            "KeyPadDivide",
            "KeyPadMultiply",
            "KeyPadSubtract",
            "KeyPadAdd",
            "KeyPadEnter",
            "KeyPadEqual",  // 336
            invalid,        // 337
            invalid,        // 338
            invalid,        // 339
            "LeftShift",    // 340
            "LeftControl",
            "LeftAlt",
            "LeftSuper",
            "RightShift",
            "RightControl",
            "RightAlt",
            "RightSuper",
            "Menu"          // 348
        };

        return key_names[intCast(key) - 256];
    }
}

Vec2d Input::Cursor::getPosition() {
    return g_input_manager.getCursorPosition();
}

void Input::Cursor::setPosition(Vec2d position) {
    g_input_manager.setCursorPosition(position);
}

} // namespace Folk