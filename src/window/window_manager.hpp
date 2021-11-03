#ifndef FOLK_WINDOW__MODULE_HPP
#define FOLK_WINDOW__MODULE_HPP

#include "../core/module.hpp"
#include "../utils/update_listener.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Folk {

FOLK_ENGINE_UPDATEABLE_MODULE(WindowManager) {
public:
    struct WindowDimentions {
        int width; 
        int height;
    };

    const char* name() const override {return "Window Manager";}

    // Set width and height of application window
    void setWindowSize(int, int);

    // Retrieve width and height of application window
    WindowDimentions const& getWindowSize();

    // Set window title
    void setWindowTitle(const char*);

    // Get ptr to GLFW window object
    GLFWwindow* windowPtr();

private:
    friend class EngineSingleton;

    GLFWwindow* window = nullptr;
    WindowDimentions window_size {800, 600};
    std::string window_title {"Folk Engine Application"};

    WindowManager();
    ~WindowManager();

    void update(Delta) override;
};

#define WINDOW WindowManager::instance()

} // namespace folk

#endif//FOLK_WINDOW__MODULE_HPP