#include "folk/scene/node.hpp"
#include "folk/core/error.hpp"

namespace Folk {

Node::Node(entt::registry &r, const char* name) : _registry(r), _name(name)
{
    _entity = _registry.create();
}

Node::~Node()
{
    for (Node* child : getChildren())
        delete child;

    _registry.destroy(_entity);
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
}

void Node::addChild(Node& node) 
{
    node.changeParent(this);
}

Node* Node::createChild() {return createChild("New Child Node");}

Node* Node::createChild(const char* name) 
{
    Node* child = new Node(_registry, name); 
    child->_parent = this;
    _children.push_back(child);
    return child;
}

Node* Node::getChild(const char* name)
{
    for (Node* ptr : _children)
        if (ptr->_name == name)
            return ptr;
    return nullptr;
}

void Node::destroy() 
{
    changeParent(nullptr);
    delete this;
}

Node::NodeList& Node::getChildren()
{
    return _children;
}

Node* Node::getParent() 
{
    return _parent;
}

}//namespace folk