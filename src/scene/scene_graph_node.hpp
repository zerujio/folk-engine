#ifndef FOLK_SCENE__SCENE_GRAPH_NODE_HPP  
#define FOLK_SCENE__SCENE_GRAPH_NODE_HPP

#include "folk/math/vector.hpp"
#include "folk/math/matrix.hpp"

#include <entt/entt.hpp>

#include <string>

namespace Folk {
    struct SceneGraphNode;
}

template<>
struct entt::component_traits<Folk::SceneGraphNode> : entt::basic_component_traits
{
    using in_place_delete = std::true_type;
};

namespace Folk
{

struct SceneGraphNode {

    friend class EntityHandle;

public:
    SceneGraphNode(const entt::entity e, const char* name) : m_id(e), m_name(name) {}

    SceneGraphNode* findChild(const char* name) const;

private:
    entt::entity m_id;

    SceneGraphNode* m_parent_ptr    {nullptr};
    SceneGraphNode* m_next_ptr      {nullptr};
    SceneGraphNode* m_prev_ptr      {nullptr};
    SceneGraphNode* m_child_ptr     {nullptr};

    std::string m_name;
    
    void changeParent(SceneGraphNode*);
};

} // namespace Folk

#endif // FOLK_SCENE__SCENE_GRAPH_NODE_HPP  