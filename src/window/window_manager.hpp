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

    static constexpr const char* name() {return "Window Manager";}

    // Set width and height of application window
    void setWindowSize(WindowDimensions);

    // Retrieve width and height of application window
    [[nodiscard]] WindowDimensions getWindowSize() const;

    // Set window title
    void setWindowTitle(const char*);

    // Get ptr to GLFW window object
    [[nodiscard]] GLFWwindow* windowPtr() const;

    void update() const noexcept;

private:
    friend class EngineSingleton;

    static constexpr WindowDimensions default_window_size {800, 600};

    GLFWwindow* window = nullptr;
    std::string window_title {"Folk Engine Application"};

    WindowManager();
    ~WindowManager();

    void pollInput() noexcept;
};

#define WINDOW WindowManager::instance()

} // namespace folk

#endif//FOLK_WINDOW__MODULE_HPP