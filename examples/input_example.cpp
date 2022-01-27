#include "folk/folk.hpp"
#include "folk/input.hpp"

#include <iostream>

using namespace Folk;

bool remapping = false; 
Key last_key = Key::Space;
InputAction* action_ptr;

void keyCallback(Key key, InputState state) {
    const char* state_str;
    switch (state) {
        case InputState::Press:
            state_str = "Press";
            break;
        case InputState::Release:
            state_str = "Release";
            break;
        case InputState::Repeat:
            state_str = "Repeat";
            break;
    }

    std::cout << Input::getKeyName(key) << ": " << state_str << "\n";

    if (key == Key::Escape && state == InputState::Press) {
        Engine::exit();
    }

    if (state == InputState::Press && remapping 
        && key != Key::LeftShift && key != Key::RightShift)
    {
        last_key = key;
    }
}

void actionCallback(InputState state) {
    if (state == InputState::Press)
        std::cout << "Hola, soy un callback!\n";
}

void rebindCallback(InputState state) {
    if (state == InputState::Press) {
        std::cout << "Remappeando...\n";
        remapping = true;
    }
    else {
        remapping = false;
        if (!action_ptr->isBound(last_key)) {
            action_ptr->bind(last_key);
            std::cout << Input::getKeyName(last_key) << " bound\n";
        }
        else {
            action_ptr->unbind(last_key);
            std::cout << Input::getKeyName(last_key) << " unbound\n";
        }
    }
}

void onClick(MouseButton mb, InputState state) {
    if (state == InputState::Release) {
        auto pos = Input::Cursor::getPosition();
        std::cout << "pos= (" << pos.x << ", " << pos.y << ")\n";
    }
}

void Folk::engineInit() {
    Folk::Engine::setPerformanceMetricsEnabled(true);
}

void Folk::sceneInit(Scene& scene) {
    scene.input.events.connect<keyCallback, Key>();
    scene.input.events.connect<onClick, MouseButton>();

    InputAction& action = scene.input.actions.create("example_action");
    action.connect<actionCallback>();
    action.bind(Key::Space);
    action_ptr = &action;

    InputAction& rebind_action = scene.input.actions.create("rebind_action");
    rebind_action.connect<rebindCallback>();
    rebind_action.bind(Key::LeftShift);
    rebind_action.bind(Key::RightShift);

    std::cout << "Mantén presionado Shift para cambiar el keybind de la acción. "
                 "Por ejemplo: presionar [Shift + A] remappaerá la acción"
                 "a la tecla A.\n"
                 "Presiona Esc para cerrar la ventana.\n";
}