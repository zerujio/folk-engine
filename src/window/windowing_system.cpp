//
// Created by sergio on 25-01-22.
//

#include "windowing_system.hpp"

#include "folk/window/glfw_call.hpp"

#include "GLFW/glfw3.h"

namespace Folk {

void WindowingSystem::initialize() {
    FOLK_GLFW_CALL(glfwInit);
    FOLK_GLFW_CALL(glfwWindowHint, GLFW_RESIZABLE, GLFW_FALSE);
    FOLK_GLFW_CALL(glfwWindowHint, GLFW_CONTEXT_VERSION_MAJOR, FOLK_OPENGL_VERSION_MAJOR);
    FOLK_GLFW_CALL(glfwWindowHint, GLFW_CONTEXT_VERSION_MINOR, FOLK_OPENGL_VERSION_MINOR);
    FOLK_GLFW_CALL(glfwWindowHint, GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void WindowingSystem::terminate() {
    FOLK_GLFW_CALL(glfwTerminate);
}

void WindowingSystem::pollEvents() {
    FOLK_GLFW_CALL(glfwPollEvents);
}

} // namespace Folk

