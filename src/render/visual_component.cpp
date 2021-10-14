#include "folk/render/visual_component.hpp"

#include "../scene/node_template_functions.hpp"

namespace Folk {

template VisualComponent& Node::addComponent();
template VisualComponent& Node::addComponent(Visual::Ref&);
template VisualComponent& Node::addComponent(Visual::Ref const&);

template VisualComponent& Node::getComponent();

template VisualComponent* Node::tryGetComponent();

} // namespace folk