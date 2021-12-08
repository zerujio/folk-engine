#ifndef FOLK_WINDOW__MODULE_HPP
#define FOLK_WINDOW__MODULE_HPP

#include "../utils/singleton.hpp"

#include <GLFW/glfw3.h>

#include <string>

namespace Folk {

FOLK_SINGLETON_CLASS_FINAL(WindowManager) {

public:
    struct WindowDimensions {
        int width; 
        int height;
    };

    const char* name() const {return "Window Manager";}

    // Set width and height of application window
    void setWindowSize(int, int);

    // Retrieve width and height of application window
    WindowDimensions const& getWindowSize();

    // Set window title
    void setWindowTitle(const char*);

    // Get ptr to GLFW window object
    GLFWwindow* windowPtr();

    void update() const noexcept;

private:
    friend class EngineSingleton;

    GLFWwindow* window = nullptr;
    WindowDimensions window_size {800, 600};
    std::string window_title {"Folk Engine Application"};

    WindowManager();
    ~WindowManager();

    void pollInput() noexcept;
};

#define WINDOW WindowManager::instance()

} // namespace folk

#endif//FOLK_WINDOW__MODULE_HPP