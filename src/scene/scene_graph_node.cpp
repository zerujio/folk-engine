#include "scene_graph_node.hpp"

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

}