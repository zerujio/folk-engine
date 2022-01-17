#include "input_manager.hpp"

namespace Folk
{

void InputManager::enqueue(Key code, InputState state) {
    m_key_queue.push(code, state);
}

void InputManager::enqueue(MouseButton code, InputState state) {
    m_mouse_queue.push(code, state);
}

void InputManager::update(const InputRegistry &registry, const ExceptionHandler &handler) noexcept {
    m_key_queue.collect<&InputManager::publish<Key>>(registry, handler);
    m_mouse_queue.collect<&InputManager::publish<MouseButton>>(registry, handler);
}

template<class InputType>
void InputManager::publish(const InputRegistry& registry,
                           const ExceptionHandler& handler,
                           const InputEvent<InputType>& event) noexcept {
    registry.template notify(event.code, event.state, handler);
    registry.notify<InputCode>(event.code, event.state, handler);
}

} // namespace folk
