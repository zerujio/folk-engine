#include "folk/scene/scene_graph_node.hpp"

#include <bx/math.h>

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

const Matrix4f& SceneGraphNode::transformMatrix() {
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
    float a[16], b[16], c[16];
    
    // scale
    bx::mtxScale(a, m_transform.scale.x, 
                    m_transform.scale.y, 
                    m_transform.scale.z);
    
    // rotation
    bx::mtxRotateY(b, m_transform.rotation.y);
    bx::mtxMul(c, a, b);

    bx::mtxRotateZ(a, m_transform.rotation.z);
    bx::mtxMul(b, c, a);

    bx::mtxRotateX(c, m_transform.rotation.x);
    bx::mtxMul(a, b, c);

    // position
    bx::mtxTranslate(b, m_transform.position.x, 
                        m_transform.position.y, 
                        m_transform.position.z);
    
    if (m_parent_ptr) {
        // c = scale * rotation * position
        bx::mtxMul(c, a, b);
        bx::mtxMul(m_transform.matrix, c, m_parent_ptr->transformMatrix());
    
    } else
        bx::mtxMul(m_transform.matrix, a, b);

    m_transform.is_mtx_valid = true;
}

}