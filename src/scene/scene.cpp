#include "folk/scene.hpp"
#include "folk/scene/scene_graph_node.hpp"

#include "../core/engine_singleton.hpp"

namespace Folk {

Scene::Scene() {
    m_registry.emplace<SceneGraphNode>(m_root, m_root, "Root");

    m_registry.on_destroy<CameraComponent>()
              .connect<&Scene::onDestroyCamera>(*this);
}

Scene::~Scene() 
try {
    m_registry.clear();
} catch(...) {
    ENGINE.log.begin(LogLevel::WARNING)
        << "An error ocurred during scene destruction:\n";
    ENGINE.exception.handleException();
    return;
}

void Scene::onDestroyCamera(entt::registry& reg, entt::entity e) {
    if (m_camera == e)
        m_camera = entt::null;
}

void Scene::setCamera(CameraPtr camera) {
    auto& comp = camera.ref;
    auto e = entt::to_entity(m_registry, comp);

    if (e == entt::null)
        throw FOLK_RUNTIME_ERROR("Entity does not belong to scene");

    m_camera = e;
}

CameraPtr Scene::getCamera() {
    if (!m_registry.valid(m_camera))
        throw FOLK_RUNTIME_ERROR("No camera set");

    entt::handle h {m_registry, m_camera};
    CameraPtr ptr {h};
    return ptr;
}

} // namespace folk