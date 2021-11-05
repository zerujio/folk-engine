#include "folk/render/visual_component.hpp"

#include "../scene/node_template_functions.hpp"

namespace Folk {

template VisualComponent& Node::addComponent();
template VisualComponent& Node::addComponent(std::shared_ptr<Visual>&);
template VisualComponent& Node::addComponent(std::shared_ptr<Visual>&&);

template VisualComponent& Node::getComponent();

template VisualComponent* Node::tryGetComponent();

} // namespace folk