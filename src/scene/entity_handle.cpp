#include "folk/scene/entity_handle.hpp"
#include "folk/scene/transform_component.hpp"
#include "folk/core/error.hpp"

#include "folk/scene/scene_graph_node.hpp"
#include "module.hpp"

namespace Folk {

bool EntityHandle::valid() const {
    return m_handle.valid();
}

void EntityHandle::destroy() {
    for (auto c : getChildren())
        c.destroy();
    m_handle.destroy();
}

SceneGraphNode& EntityHandle::node() const {
    return m_handle.get<SceneGraphNode>();
}

const std::string& EntityHandle::name() const {
    return node().m_name;
}

void EntityHandle::addChild(const EntityHandle& e) const {
    auto& other = e.node();

    if (other.m_parent_ptr)
        throw EngineRuntimeError("Can't add root entity as child");

    other.changeParent(&node());
}

EntityHandle EntityHandle::createChild(const char* name) const {
    entt::handle new_handle = {*m_handle.registry(), 
                               m_handle.registry()->create()};
    // add as child
    auto& new_node = new_handle.emplace<SceneGraphNode>(new_handle, name);
    new_node.changeParent(&node());

    return {new_handle};
}

EntityHandle EntityHandle::createChild() const {
    return createChild("New entity");
}

std::optional<EntityHandle> EntityHandle::getChild(const char* name) const
{
    auto ptr = node().findChild(name);

    if (ptr) {
        auto& registry = *m_handle.registry();
        return {entt::handle(registry, ptr->m_id)};
    }
    
    return {};
}

EntityHandle::HandleList EntityHandle::getChildren() const
{
    HandleList list;

    auto& reg = *m_handle.registry();
    for (auto ptr = node().m_child_ptr; ptr; ptr = ptr->m_next_ptr) {
        auto id = ptr->m_id;
        list.emplace_back(reg, id);
    }

    return list;
}

std::optional<EntityHandle> EntityHandle::getParent() const
{
    auto parent = node().m_parent_ptr;

    if (parent) {
        auto& reg = *m_handle.registry();
        auto id = parent->m_id;

        return {entt::handle(reg, id)};
    }

    return {};
}

}//namespace folk