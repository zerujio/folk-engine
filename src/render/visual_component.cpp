#include "folk/render/visual_component.hpp"

namespace Folk {

VisualComponent& VisualComponent::emplaceComponent(const entt::handle handle) {
    return handle.emplace<VisualComponent>();
}

VisualComponent& VisualComponent::emplaceComponent(const entt::handle handle,
                                                   std::shared_ptr<Visual> vs)
{
    return handle.emplace<VisualComponent>(vs);
}

VisualComponent* VisualComponent::getComponent(const entt::handle handle) {
    return handle.try_get<VisualComponent>();
}

bool removeComponent(const entt::handle handle) {
    return handle.remove<VisualComponent>();
}

} // namespace folk