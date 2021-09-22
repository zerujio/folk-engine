#ifndef FOLK_WINDOW__MODULE_HPP
#define FOLK_WINDOW__MODULE_HPP

#include <string>
#include <GLFW/glfw3.h>
#include "../engine/engine_module.hpp"

namespace folk {

FOLK_ENGINE_MODULE_SINGLETON(WindowModule) {
public:
    FOLK_ENGINE_MODULE_NAME_FUNCTION("Window")

    struct WindowDimentions {
        GLuint width = 800; 
        GLuint height = 600;
    };

    // Set width and height of application window
    void setWindowSize(GLuint, GLuint);

    // Retrieve width and height of application window
    WindowDimentions const& getWindowSize();

    // Set window title
    void setWindowTitle(const char*);

    // Get ptr to GLFW window object
    GLFWwindow* getWindowPtr();

private:
    GLFWwindow* window = nullptr;
    WindowDimentions window_size;
    std::string window_title {"Unnamed Folk Engine Application"};

    void onStartUp();
    void onShutDown();
};

} // namespace folk

#define WINDOW WindowModule::instance

#endif//FOLK_WINDOW__MODULE_HPP