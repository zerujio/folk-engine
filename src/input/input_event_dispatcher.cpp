//
// Created by sergio on 06-01-22.
//

#include "folk/input/input_event_dispatcher.hpp"

namespace Folk {

void InputEventDispatcher::update(const ExceptionHandler& handler) {
    update<Key>(handler);
    update<MouseButton>(handler);
    update<InputCode>(handler);
}

// ConnectionManager



} // namespace Folk