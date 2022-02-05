//
// Created by sergio on 25-01-22.
//

#include "windowing_system.hpp"

#include "folk/window/glfw_call.hpp"

#include "GLFW/glfw3.h"

namespace Folk {

void WindowingSystem::initialize() {
    GLFW::call::slow(glfwInit)();
    GLFW::call::slow(glfwWindowHint)(GLFW_RESIZABLE, GLFW_FALSE);
    GLFW::call::slow(glfwWindowHint)(GLFW_CONTEXT_VERSION_MAJOR, FOLK_OPENGL_VERSION_MAJOR);
    GLFW::call::slow(glfwWindowHint)(GLFW_CONTEXT_VERSION_MINOR, FOLK_OPENGL_VERSION_MINOR);
    GLFW::call::slow(glfwWindowHint)(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef FOLK_DEBUG
    GLFW::call::slow(glfwWindowHint)(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
}

void WindowingSystem::terminate() {
    GLFW::call::slow(glfwTerminate);
}

void WindowingSystem::pollEvents() {
    GLFW::call::slow(glfwPollEvents)();
}

} // namespace Folk

