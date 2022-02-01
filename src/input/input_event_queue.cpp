#include "folk/input/input_event_queue.hpp"

namespace Folk
{

void InputEventQueue::enqueue(Key code, InputState state) {
    m_key_queue.push(code, state);
}

void InputEventQueue::enqueue(MouseButton code, InputState state) {
    m_mouse_queue.push(code, state);
}

void InputEventQueue::update(const InputRegistry &registry, const ExceptionHandler &handler) noexcept {
    m_key_queue.collect<&InputEventQueue::publish<Key>>(registry, handler);
    m_mouse_queue.collect<&InputEventQueue::publish<MouseButton>>(registry, handler);
}

template<class InputType>
void InputEventQueue::publish(const InputRegistry& registry,
                              const ExceptionHandler& handler,
                              const InputEvent<InputType>& event) noexcept {
    registry.template notify(event.code, event.state, handler);
    registry.notify<InputCode>(event.code, event.state, handler);
}

} // namespace folk
