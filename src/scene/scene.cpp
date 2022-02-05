#include "folk/scene.hpp"
#include "folk/scene/scene_graph_node.hpp"

#include "../core/engine.hpp"

namespace Folk {

Scene::Scene() {
    m_entity_registry.emplace<SceneGraphNode>(m_root, m_root, "Root");

    m_entity_registry.on_destroy<CameraComponent>().connect<&Scene::onDestroyCamera>(*this);
}

Scene::~Scene() {
    m_entity_registry.clear();
}

void Scene::onDestroyCamera(const entt::registry&, entt::entity e) {
    if (m_camera == e)
        m_camera = entt::null;
}

void Scene::setCamera(CameraPtr camera) {
    auto& comp = camera.ref;
    auto e = entt::to_entity(m_entity_registry, comp);

    if (e == entt::null)
        throw Error("Entity does not belong to scene");

    m_camera = e;
}

CameraPtr Scene::getCamera() {
    if (!m_entity_registry.valid(m_camera))
        throw Error("No camera set");

    entt::handle h {m_entity_registry, m_camera};
    CameraPtr ptr {h};
    return ptr;
}

} // namespace folk