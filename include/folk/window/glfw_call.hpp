//
// Created by sergio on 25-01-22.
//

#ifndef SRC_WINDOW__GLFW_CALL_HPP
#define SRC_WINDOW__GLFW_CALL_HPP

#include "folk/error.hpp"
#include "folk/utils/library_call.hpp"

#include <optional>

namespace Folk::GLFW {

struct GLFWError : public Folk::Error {
    using Error::Error;
};

std::optional<const char*> getError();

using call = LibCall<getError>;

}

#endif //SRC_WINDOW__GLFW_CALL_HPP
