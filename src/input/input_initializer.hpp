//
// Created by sergio on 26-01-22.
//

#ifndef SRC_INPUT__INPUT_INITIALIZER_HPP
#define SRC_INPUT__INPUT_INITIALIZER_HPP

#include "folk/input.hpp"
#include "input_manager.hpp"
#include "input_event_queue.hpp"

namespace Folk {

struct Input::ScopedInitializer final {
    ScopedInitializer(InputManager input_manager, InputEventQueue& input_queue);
    ScopedInitializer(const ScopedInitializer &) = delete;
    ScopedInitializer& operator=(const ScopedInitializer &) = delete;
    ~ScopedInitializer();
};

} // namespace Folk

#endif //SRC_INPUT__INPUT_INITIALIZER_HPP
