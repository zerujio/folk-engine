//
// Created by sergio on 07-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__MOUSE_BUTTON_HPP
#define INCLUDE_FOLK_INPUT__MOUSE_BUTTON_HPP

#include "common.hpp"

namespace Folk {

/// Botones del mouse.
enum class MouseButton : INPUT_CODE_INT_TYPE {
    Left,
    Right,
    Middle,
    Extra1,
    Extra2,
    Extra3,
    Extra4,
    Extra5
};

}

#endif //INCLUDE_FOLK_INPUT__MOUSE_BUTTON_HPP
