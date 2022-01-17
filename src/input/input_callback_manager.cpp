//
// Created by sergio on 13-01-22.
//

#include "../../include/folk/input/input_callback_manager.hpp"

namespace Folk {

template<>
InputCallbackManager::Sink<Key>& InputCallbackManager::getSink<Key>() { return m_key_sink; }

template<>
InputCallbackManager::Sink<MouseButton>& InputCallbackManager::getSink<MouseButton>() { return m_mb_sink; }

template<>
InputCallbackManager::Sink<InputCode>& InputCallbackManager::getSink<InputCode>() { return m_code_sink; }

} // namespace Folk
