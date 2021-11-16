#include "folk/scene/scene.hpp"
#include "folk/scene/scene_graph_node.hpp"

namespace Folk {

Scene::Scene() {
    m_registry.emplace<SceneGraphNode>(m_root, m_root, "Root");

    m_registry.on_destroy<CameraComponent>()
              .connect<&Scene::onDestroyCamera>(*this);
}

void Scene::onDestroyCamera(entt::registry& reg, entt::entity e) {
    if (m_camera == e)
        m_camera = entt::null;
}

void Scene::setCamera(CameraPtr camera) {
    auto& comp = camera.ref;
    auto e = entt::to_entity(m_registry, comp);

    if (e == entt::null)
        throw EngineRuntimeError("Entity does not belong to scene");

    m_camera = e;
}

CameraPtr Scene::getCamera() {
    entt::handle h {m_registry, m_camera};
    CameraPtr ptr {h};
    return ptr;
}

} // namespace folk