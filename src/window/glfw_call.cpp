//
// Created by sergio on 26-01-22.
//

#include "glfw_call.hpp"

#include "GLFW/glfw3.h"

namespace Folk::GLFW {

std::optional<const char*> getError() {
    const char* description {nullptr};

    if (glfwGetError(&description) != GLFW_NO_ERROR)
        return {description};

    return {}; // no error
}

}

