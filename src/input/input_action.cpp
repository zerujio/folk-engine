#include "folk/input/input_action.hpp"
#include "input_manager.hpp"

namespace Folk
{

IdIntType InputAction::next_id_ = 0;

InputAction::InputAction(InputAction && other) 
    : bindings_(std::move(other.bindings_)), 
      callbacks_(std::move(other.callbacks_))
{}

InputAction& InputAction::create(std::string const& name) {
    auto& actions = INPUT.actions_;

    auto [iter, success] = actions.emplace(name, InputActionProxy());
    
    if (not success)
        throw FOLK_RUNTIME_ERROR("InputAction named " + name + " already exists\n");

    return iter->second.action;
}

InputAction& InputAction::get(std::string const& name) {
    auto& actions = INPUT.actions_;

    auto iter = actions.find(name);

    if (iter == actions.end())
        throw FOLK_RUNTIME_ERROR("No InputAction named " + name + "\n");
    
    return iter->second.action;
}

void InputAction::destroy(std::string const& name) {
    auto& actions = INPUT.actions_;

    auto iter = actions.find(name);

    if (iter == actions.end())
        throw FOLK_RUNTIME_ERROR("No InputAction named " + name + "\n");

    actions.erase(iter);
}

InputAction::CallbackId InputAction::addCallback(CallbackType &&func) {
    auto id = next_id_++;
    callbacks_.emplace(id, func);
    return static_cast<CallbackId>(id);
}

void InputAction::removeCallback(CallbackId id) {
    callbacks_.erase(static_cast<IdIntType>(id));
}

InputState InputAction::state() const {   
    for (auto const& binding : bindings_)
        if (binding.state() == InputState::Press)
            return InputState::Press;
    return InputState::Release;
}

void InputAction::addBinding(InputCode const code) {
    auto [iter, inserted] = bindings_.insert(code);
    if (inserted)
        bind(code);
}

void InputAction::removeBinding(InputCode const code) {
    auto iter = bindings_.find(code);
    if (iter != bindings_.end()) {
        bindings_.erase(iter);
        unbind(code);
    }
}

void InputAction::clearBindings() {
    for (auto code : bindings_)
        unbind(code);
    
    bindings_.clear();
}

void InputAction::bind(InputCode const code) {
    INPUT.bindings_.emplace(code, this);
}

void InputAction::unbind(InputCode const code) {
    auto [begin, end] = INPUT.bindings_.equal_range(code);
    for (auto it = begin; it != end; ++it)
        if (it->second == this) {
            INPUT.bindings_.erase(it);
            break;
        }
}

} // namespace Folk
