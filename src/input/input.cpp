#include "folk/input/input.hpp"

#include "../core/engine_singleton.hpp"

#include "input_manager.hpp"
#include "utils.hpp"

namespace Folk
{

// Polling functions 

InputState getKey(Key key) {
    return static_cast<InputState>(glfwGetKey(ENGINE.window.getWindowPtr(), 
                                   intCast(key)));
}

const char* getKeyName(Key key) {
    if (key == Key::Space)
        return "Space";
    
    else if (intCast(key) < 256) {
        return glfwGetKeyName(intCast(key), 0);
    
    }
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

InputState getMouseButton(MouseButton mb) {
    return static_cast<InputState>(
        glfwGetMouseButton(ENGINE.window.getWindowPtr(), intCast(mb))
    );
}

// InputCode
InputState InputCode::state() const {
    if (isMouseButton())
        return stateCast(glfwGetMouseButton(ENGINE.window.getWindowPtr(),
                                            intCast(operator MouseButton())));
    else
        return stateCast(glfwGetKey(ENGINE.window.getWindowPtr(),
                                    intCast(operator Key())));
}


// Callback registering functions
IdIntType InputManager::next_id = 0;

Key_CallbackId addKeyCallback(Key_CallbackType &&f) {
    auto id = INPUT.next_id++;
    INPUT.key_callbacks_.emplace(id, f);
    return static_cast<Key_CallbackId>(id);
}

void removeKeyCallback(Key_CallbackId const id)  {
    INPUT.key_callbacks_.erase(static_cast<IdIntType>(id));
}


MouseButton_CallbackId addMouseButtonCallback(MouseButton_CallbackType &&f) {
    auto id = INPUT.next_id++;
    INPUT.mouse_btn_callbacks_.emplace(id, f);
    return static_cast<MouseButton_CallbackId>(id);
}

void removeMouseButtonCallback(MouseButton_CallbackId const id) {
    INPUT.mouse_btn_callbacks_.erase(static_cast<IdIntType>(id));
}


InputCode_CallbackId addInputCodeCallback(InputCode_CallbackType &&f) {
    auto id = INPUT.next_id++;
    INPUT.input_code_callbacks_.emplace(id, f);
    return static_cast<InputCode_CallbackId>(id);
}

void removeInputCodeCallback(InputCode_CallbackId const id) {
    INPUT.input_code_callbacks_.erase(static_cast<IdIntType>(id));
}

} // namespace Folk