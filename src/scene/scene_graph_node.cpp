#include "folk/scene/scene_graph_node.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Folk {

void SceneGraphNode::changeParent(SceneGraphNode* new_parent_ptr) {
    if (m_parent_ptr)
        m_parent_ptr->m_child_ptr = m_prev_ptr ? m_prev_ptr : m_next_ptr;
    
    if (m_next_ptr)
        m_next_ptr->m_prev_ptr = m_prev_ptr;
    
    if (m_prev_ptr)
        m_prev_ptr->m_next_ptr = m_next_ptr;

    m_parent_ptr = new_parent_ptr;
    m_prev_ptr = nullptr;

    if (new_parent_ptr) {
        m_next_ptr = new_parent_ptr->m_child_ptr;
        if (m_next_ptr)
            m_next_ptr->m_prev_ptr = this;

        new_parent_ptr->m_child_ptr = this;

    } else
        m_next_ptr = nullptr;
}

SceneGraphNode* SceneGraphNode::findChild(const char* name) const {
    for (auto ptr = m_child_ptr; ptr; ptr = ptr->m_next_ptr)
        if (ptr->m_name == name)
            return ptr;
    return nullptr;
}

const Mat4& SceneGraphNode::transformMatrix() {
    if (!m_transform.is_mtx_valid)
        updateTransformMatrix();
    
    return m_transform.matrix;
}

void SceneGraphNode::invalidateMtxCache() {
    m_transform.is_mtx_valid = false;

    for (auto ptr = m_child_ptr; ptr; ptr = ptr->m_next_ptr)
        ptr->invalidateMtxCache();
}

void SceneGraphNode::updateTransformMatrix() {
    Mat4 transform {1.0f};

    // position
    transform = glm::translate(transform, m_transform.position);
    
    // rotation
    transform = glm::rotate(transform, glm::radians(m_transform.rotation.x), {1.0f, .0f, .0f});
    transform = glm::rotate(transform, glm::radians(m_transform.rotation.z), {.0f, .0f, 1.0f});
    transform = glm::rotate(transform, glm::radians(m_transform.rotation.y), {.0f, 1.0f, .0f});

    // scale
    transform = glm::scale(transform, m_transform.scale);
    
    if (m_parent_ptr)
        transform = m_parent_ptr->transformMatrix() * transform;

    m_transform.matrix = transform;
    m_transform.is_mtx_valid = true;
}

const Vec3 &SceneGraphNode::position() const noexcept {
    return m_transform.position;
}

const Vec3 &SceneGraphNode::rotation() const noexcept {
    return m_transform.rotation;
}

const Vec3 &SceneGraphNode::scale() const noexcept {
    return m_transform.scale;
}

}