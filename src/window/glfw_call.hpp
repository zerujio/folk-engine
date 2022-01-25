//
// Created by sergio on 25-01-22.
//

#ifndef SRC_WINDOW__GLFW_CALL_HPP
#define SRC_WINDOW__GLFW_CALL_HPP

#include <type_traits>

#include "GLFW/glfw3.h"

namespace Folk::GLFW {

struct Error : public RuntimeError {
    using RuntimeError::RuntimeError;
};

void checkErrors(const char* file, int line, const char* function)
{
    const char* description {nullptr};

    if (glfwGetError(&description) != GLFW_NO_ERROR)
        throw Error(description, file, line, function);
}

#define FOLK_GLFW_CALL(expression) expression GLFW::checkErrors(__FILE__, __LINE__, __PRETTY_FUNCTION__);

}

#endif //SRC_WINDOW__GLFW_CALL_HPP
