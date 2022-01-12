#include "folk/folk.hpp"
#include "folk/input.hpp"

#include <iostream>
#include <set>

using namespace Folk;

bool remapping = false; 
InputCode last_key = Key::Space;
InputAction* action_ptr;

void keyCallback(Key key, InputState state) {
    std::cout << getKeyName(key) << ": " 
              << ((state == InputState::Press) ? "press" : "release") << "\n";

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
        if (action_ptr->bindings().count(last_key) == 0) {
            action_ptr->bind(last_key);
            std::cout << getKeyName(last_key) << " bound\n";
        }
        else {
            action_ptr->unbind(last_key);
            std::cout << getKeyName(last_key) << " unbound\n";
        }
    }
}

void onClick(MouseButton mb, InputState state) {
    if (state == InputState::Release) {
        auto pos = Cursor::getPosition();
        std::cout << "pos= (" << pos.x << ", " << pos.y << ")\n";
    }
}

void Folk::engineInit() {
    Folk::Engine::setPerformanceMetricsEnabled(true);
}

void Folk::sceneInit(Scene& scene) {
    auto id = addKeyCallback(keyCallback);
    auto mb_id = addMouseButtonCallback(onClick);

    InputAction& action = InputAction::create("example_action");
    action.addCallback(actionCallback);
    action.bind(Key::Space);
    action_ptr = &action;

    InputAction& rebind_action = InputAction::create("rebind_action");
    rebind_action.addCallback(rebindCallback);
    rebind_action.bind(Key::LeftShift);
    rebind_action.bind(Key::RightShift);

    std::cout << "Mantén presionado Shift para cambiar el keybind de la acción. "
                 "Por ejemplo: presionar [Shift + A] remappaerá la acción"
                 "a la tecla A.\n"
                 "Presiona Esc para cerrar la ventana.\n";
}