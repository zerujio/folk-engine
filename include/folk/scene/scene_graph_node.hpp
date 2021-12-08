#ifndef FOLK_SCENE__SCENE_GRAPH_NODE_HPP  
#define FOLK_SCENE__SCENE_GRAPH_NODE_HPP

#include "folk/math/vector.hpp"
#include "folk/math/matrix.hpp"

#include <entt/entt.hpp>

#include <string>

namespace Folk {
    struct SceneGraphNode;
    class TransformPtr;
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
    friend class TransformPtr;

public:
    using ptr_type = TransformPtr;
    static constexpr const char* type_name = "SceneGraphNode+Transform";

    SceneGraphNode(const entt::entity e, const char* name) : m_id(e), m_name(name) {}

    SceneGraphNode* findChild(const char* name) const;

    const Matrix4f& transformMatrix();

    const Vec3f& position() const noexcept;
    const Vec3f& rotation() const noexcept;
    const Vec3f& scale() const noexcept;

private:
    entt::entity m_id;

    SceneGraphNode* m_parent_ptr    {nullptr};
    SceneGraphNode* m_next_ptr      {nullptr};
    SceneGraphNode* m_prev_ptr      {nullptr};
    SceneGraphNode* m_child_ptr     {nullptr};

    std::string m_name;

    struct Transform {
        Vec3f position {0, 0, 0};
        Vec3f rotation {0, 0, 0};
        Vec3f scale    {1, 1, 1};
        
        Matrix4f matrix;

        // is transform matrix valid (up to date)?
        bool is_mtx_valid {false};
    };

    Transform m_transform;
    
    void changeParent(SceneGraphNode*);

    // recursively invalidate matrix cache.
    void invalidateMtxCache();

    // recalculate transform matrix
    void updateTransformMatrix();
};

} // namespace Folk

#endif // FOLK_SCENE__SCENE_GRAPH_NODE_HPP  