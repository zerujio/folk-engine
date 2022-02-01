//
// Created by sergio on 25-01-22.
//

#ifndef SRC_WINDOW__GLFW_CALL_HPP
#define SRC_WINDOW__GLFW_CALL_HPP

#include "folk/utils/library_call.hpp"

#include <optional>

namespace Folk::GLFW {

struct Error : public RuntimeError {
    using RuntimeError::RuntimeError;
};

std::optional<const char*> getError();
}

#define FOLK_GLFW_CALL(function, ...) FOLK_C_LIBRARY_CALL(GLFW::getError, function, ##__VA_ARGS__)

#endif //SRC_WINDOW__GLFW_CALL_HPP
