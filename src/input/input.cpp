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
    std::cout << intCast(key) << "\n";
    if (key == Key::Space)
        return "Space";
    else if (intCast(key) < 256) {
        std::cout << "<256\n";
        return glfwGetKeyName(intCast(key), 0);
    }
    else {
        std::cout << ">=256\n";
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

static CallbackId next_callback_id = 0;

CallbackId addKeyCallback(KeyCallbackT f) {
    auto id = next_callback_id++;
    INPUT.key_callbacks.emplace(id, f);
    return id;
}

void removeKeyCallback(CallbackId id)  {
    INPUT.key_callbacks.erase(id);
}

CallbackId addMouseButtonCallback(MouseButtonCallbackT f) {
    auto id = next_callback_id++;
    INPUT.mouse_btn_callbacks.emplace(id, f);
    return id;
}

void removeMouseButtonCallback(CallbackId id) {
    INPUT.mouse_btn_callbacks.erase(id);
}

CallbackId addInputCodeCallback(InputCodeCallbackT f) {
    auto id = next_callback_id++;
    INPUT.input_code_callbacks.emplace(id, f);
    return id;
}

// InputCombination

constexpr bool operator==(InputCombination x, InputCombination y) {
    // array of 4 uint16_t = 1 uint64_t
    return *((uint64_t*) x.codes) == *((uint64_t*) y.codes);
}

constexpr bool operator!=(InputCombination x, InputCombination y) {
    return !(x == y);
}

InputState InputCombination::state() const {

    for (int i = 0; i < 4; ++i) {
        auto code = codes[i];
        if (code && code.state() == InputState::Release)
            return InputState::Release;
    }

    return InputState::Press;
}


// InputAction

InputAction::CallbackId InputAction::next_id = 0;

InputAction::CallbackId InputAction::addCallback(CallbackType func) {
    auto id = next_id++;
    callbacks_.emplace(id, func);
    return id;
}

void InputAction::removeCallback(CallbackId id) {
    callbacks_.erase(id);
}

InputState InputAction::state() const {   
    for (auto const& binding : bindings_)
        if (binding.state() == InputState::Press)
            return InputState::Press;
    return InputState::Release;
}

uint InputAction::addBinding(InputCombination cmb) {
    auto index = bindings_.size();
    bindings_.emplace_back(this, cmb);
    return index;
}

void InputAction::changeBinding(uint k, InputCombination combination) {
    if (k >= bindings_.size())
        throw EngineRuntimeError("Binding index out of range");
}

void InputAction::removeBinding(uint k) {
    if (k >= bindings_.size())
        throw EngineRuntimeError("Binding index out of range");
    
    auto it = bindings_.begin();
    it += k;
    bindings_.erase(it);
}


// InputAction::Binding

InputAction::Binding::Binding(InputAction *act, InputCombination cmb) 
: action_(act), combination_(cmb)
{
    for (uint i = 0; i < 4; ++i) {
        if (combination_[i]) {
            ENGINE.input_manager
                  .input_bindings_[combination_[i]]
                  .insert(this);
        }
    }
}

InputAction::Binding::Binding(Binding const& other) 
: Binding(other.action_, other.combination_)
{
    *((uint64_t*) state_) = *((uint64_t*) other.state_);
}

InputAction::Binding::Binding(Binding&& other) 
: Binding(other.action_, other.combination_)
{
    *((uint64_t*) state_) = *((uint64_t*) other.state_);
}

InputAction::Binding::~Binding() {
    for (int i = 0; i < 4; ++i) {
        auto code = combination_[i];
        if (code) {
            ENGINE.input_manager
                  .input_bindings_[code]
                  .erase(this);
        }
    }
}

void InputAction::Binding::changeCombination(InputCombination cmb) {
    for (int i = 0; i < 4; ++i) {
        const auto new_code = cmb[i];
        const auto old_code = combination_[i];
        
        if (new_code != old_code) {
            if (old_code)
                ENGINE.input_manager
                      .input_bindings_[old_code]
                      .erase(this);
            if (new_code)
                ENGINE.input_manager
                      .input_bindings_[new_code]
                      .insert(this);
        }
    }
    combination_ = cmb;
}

InputAction::Binding& InputAction::Binding::operator=(Binding const& other) {
    changeCombination(other.combination_);
    action_ = other.action_;
    *((uint64_t*) state_) = *((uint64_t*) other.state_);

    return *this;
}

InputState InputAction::Binding::state() const {
    if (   (combination_[0] && state_[0] == InputState::Release)
        || (combination_[1] && state_[1] == InputState::Release)
        || (combination_[2] && state_[2] == InputState::Release)
        || (combination_[3] && state_[3] == InputState::Release) )
        return InputState::Release;
    return InputState::Press;
}

} // namespace Folk