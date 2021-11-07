#include "folk/scene/node.hpp"
#include "folk/scene/transform_component.hpp"
#include "folk/core/error.hpp"

#include "module.hpp"

namespace Folk {

Node::Node(const char* name) 
    : _name(name), _id(SCENE.registry.create())
{
    addComponent<TransformComponent>();
}

Node::~Node()
{
    for (Node* child : getChildren())
        delete child;

    SCENE.registry.destroy(_id);
}

void Node::changeParent(Node* p) 
{
    if (_parent) {
        auto& nodelist = _parent->_children;
        for (auto it = nodelist.begin(); it != nodelist.end(); ++it) {
            if (*it = this) {
                nodelist.erase(it);
                break;
            }
        }
    }

    _parent = p;

    if (p)
        p->_children.push_back(this);

    onParentChange();
}

void Node::addChild(Node& node) 
{
    if (node._parent)
        node.changeParent(this);
    else
        throw EngineRuntimeError("Attempt to add root node as child");
}

Node& Node::createChild() {
    return createChild("NewChildNode");
}

Node& Node::createChild(const char* name) 
{
    Node* child = new Node(name); 
    child->_parent = this;
    _children.push_back(child);
    child->onParentChange();
    return *child;
}

Node& Node::getChild(const char* name)
{
    for (Node* ptr : _children)
        if (ptr->_name == name)
            return *ptr;
    
    throw EngineRuntimeError("Node " + _name + " has no child named " + name);
}

void Node::destroy() 
{
    changeParent(nullptr);
    delete this;
}

Node::NodeList const& Node::getChildren()
{
    return _children;
}

Node& Node::getParent() 
{
    if (_parent)
        return *_parent;
    throw EngineRuntimeError("Node " + _name + " has no parent");
}

void Node::onParentChange() {
    auto& tr = getComponent<TransformComponent>();

    tr.m_parent_id = _parent ? _parent->_id : entt::null;
    tr.m_modified = true;

    for (auto c : _children)
        c->onParentChange();
}

}//namespace folk