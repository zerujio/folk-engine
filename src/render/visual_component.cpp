#include "folk/render/visual_component.hpp"

#include "../scene/module.hpp"

namespace Folk {

VisualComponent& VisualComponent::emplaceComponent(const Node::Id id) {
    return SCENE.registry.emplace<VisualComponent>(id);
}

VisualComponent& VisualComponent::emplaceComponent(const Node::Id id,
                                                   std::shared_ptr<Visual> vs)
{
    return SCENE.registry.emplace<VisualComponent>(id, vs);
}

VisualComponent* VisualComponent::getComponent(const Node::Id id) {
    return SCENE.registry.try_get<VisualComponent>(id);
}

bool removeComponent(const Node::Id id) {
    return SCENE.registry.remove<VisualComponent>(id);
}

} // namespace folk