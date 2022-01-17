#ifndef FOLK_INPUT__INPUT_MANAGER
#define FOLK_INPUT__INPUT_MANAGER

#include "../utils/singleton.hpp"
#include "../utils/simple_queue.hpp"

#include "folk/core/exception_handler.hpp"

#include "folk/input/input_registry.hpp"

#include <map>
#include <string>

namespace Folk
{

#define INPUT InputManager::instance()
FOLK_SINGLETON_CLASS_FINAL(InputManager) {

public:
    void enqueue(Key code, InputState state);
    void enqueue(MouseButton code, InputState state);

    /// Deliver queued input events to a scene (via an input registry).
    void update(const InputRegistry& registry, const ExceptionHandler& handler) noexcept;

private:
    template<class InputType>
    struct InputEvent {
        InputType code;
        InputState state;

        InputEvent(InputType code_, InputState state_) : code(code_), state(state_) {}
    };

    SimpleQueue<InputEvent<Key>> m_key_queue {8};
    SimpleQueue<InputEvent<MouseButton>> m_mouse_queue {8};

    template<class InputType>
    static void publish(const InputRegistry& registry,
                        const ExceptionHandler& handler,
                        const InputEvent<InputType>& event) noexcept;
};

} // namespace folk

#endif // FOLK_INPUT__INPUT_MANAGER