#ifndef FOLK_WINDOW__MODULE_HPP
#define FOLK_WINDOW__MODULE_HPP

#include <string>
#include <GLFW/glfw3.h>
#include "../utils/singleton.hpp"
#include "../utils/update_listener.hpp"

namespace folk {

FOLK_SINGLETON_CLASS_FINAL(WindowModule), public UpdateListener {
public:
    struct WindowDimentions {
        GLuint width; 
        GLuint height;
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
    friend class EngineSingleton;

    GLFWwindow* window = nullptr;
    WindowDimentions window_size {800, 600};
    std::string window_title {"Unnamed Folk Engine Application"};

    WindowModule();
    ~WindowModule();

    void update(double) override;
};

#define WINDOW WindowModule::instance()

} // namespace folk

#endif//FOLK_WINDOW__MODULE_HPP