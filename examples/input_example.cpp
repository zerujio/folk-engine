#include "folk/folk.hpp"
#include "folk/input/input.hpp"

#include <iostream>

using namespace Folk;

void keyCallback(Key key, InputState state) {
    std::cout << getKeyName(key) << ": " 
              << ((state == InputState::Press) ? "Press" : "Release") << "\n";

    if (key == Key::Escape && state == InputState::Press) {
        Engine::exit();
    }
}

void Folk::engineInit() {
    
}

void Folk::sceneInit(Scene& scene) {
    auto id = addKeyCallback(keyCallback);
}