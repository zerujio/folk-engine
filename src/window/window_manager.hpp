#ifndef FOLK_WINDOW__MODULE_HPP
#define FOLK_WINDOW__MODULE_HPP

#include "../utils/singleton.hpp"

#include "../input/input_manager.hpp"

#include "folk/input/key.hpp"
#include "folk/input/mouse_button.hpp"
#include "folk/input/input_code.hpp"

#include "GLFW/glfw3.h"

#include "entt/entt.hpp"

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

    InputState getKey(Key);
    InputState getMouseButton(MouseButton);
    InputState getInput(InputCode);

    GLFWwindow* windowPtr() { return window; }

private:
    friend class EngineSingleton;

    static constexpr WindowDimensions default_window_size {800, 600};

    GLFWwindow* window = nullptr;
    std::string window_title {"Folk Engine Application"};
    entt::delegate<void(Key, InputState)> m_keyCallback;
    entt::delegate<void(MouseButton, InputState)> m_mouseButtonCallback;

    explicit WindowManager(InputManager& input_manager);
    ~WindowManager();

    void update() const noexcept;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow*, int button, int action, int mods);
};

#define WINDOW WindowManager::instance()

} // namespace folk

#endif//FOLK_WINDOW__MODULE_HPP