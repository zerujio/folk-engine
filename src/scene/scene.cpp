#include "folk/scene/scene.hpp"

#include "scene_graph_node.hpp"

namespace Folk {

Scene::Scene() {
    m_registry.emplace<SceneGraphNode>(m_root, m_root, "Root");
}

} // namespace folk