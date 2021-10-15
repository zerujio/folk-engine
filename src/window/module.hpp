#ifndef FOLK_WINDOW__MODULE_HPP
#define FOLK_WINDOW__MODULE_HPP

#include "../core/module.hpp"
#include "../utils/update_listener.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>

namespace Folk {

FOLK_ENGINE_UPDATEABLE_MODULE(WindowModule) {
public:
    struct WindowDimentions {
        GLuint width; 
        GLuint height;
    };

    const char* name() const override {return "window_manager";}

    // Set width and height of application window
    void setWindowSize(GLuint, GLuint);

    // Retrieve width and height of application window
    WindowDimentions const& getWindowSize();

    // Set window title
    void setWindowTitle(const char*);

    // Get ptr to GLFW window object
    GLFWwindow* getWindowPtr();

private:
    friend class EngineSingleton;

    GLFWwindow* window = nullptr;
    WindowDimentions window_size {800, 600};
    std::string window_title {"Folk Engine Application"};

    WindowModule();
    ~WindowModule();

    void update(Delta) override;
};

#define WINDOW WindowModule::instance()

} // namespace folk

#endif//FOLK_WINDOW__MODULE_HPP