//
// Created by sergio on 25-01-22.
//

#include "windowing_system.hpp"

#include "glfw_call.hpp"

#include "GLFW/glfw3.h"

namespace Folk {

void WindowingSystem::startUp() {
    FOLK_GLFW_CALL(glfwInit);
}

void WindowingSystem::shutDown() {
    FOLK_GLFW_CALL(glfwTerminate);
}

void WindowingSystem::pollEvents() {
    FOLK_GLFW_CALL(glfwPollEvents);
}

} // namespace Folk

