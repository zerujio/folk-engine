//
// Created by sergio on 14-01-22.
//

#include "folk/input/input_registry.hpp"

namespace Folk {

InputRegistryManager::InputRegistryManager(InputRegistry &registry)
: events(registry.m_event_registry), actions(registry.m_action_registry)
{}

} // namespace Folk