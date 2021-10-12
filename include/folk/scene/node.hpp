#ifndef FOLK_SCENE__NODE_HPP
#define FOLK_SCENE__NODE_HPP

#include "folk/core/error.hpp"

#include <entt/entt.hpp>

#include <string>
#include <vector>

namespace folk {

class Scene;

/// A scene graph node
class Node {
public:
    Node(const Node&) = delete;
    Node& operator= (const Node&) = delete;
    ~Node();

    /// Add node as child. This will change said nodes' parent to *this.
    /**
     * @param n node to add as child.
    */
    void addChild(Node& n);

    /// Add a new, empty node as child of this node and return a reference.
    Node* createChild(const char*);
    Node* createChild();

    /// Find a child by name.
    /**
     * @param name name of the child to retrieve.
     */
    Node* getChild(const char* name);

    /// Destroy this node.
    void destroy();

    using NodeList = std::vector<Node*>;

    /// Return a list of pointers to this node's children.
    NodeList& getChildren();

    /// Retrieve this node's parent.
    Node* getParent();

    std::string& name() {return _name;}

    /// Add a component to this node.
    /**
     * Adding a component to a node that already has said component will result
     * in a an exception.
     * 
     * @param <C> the type of component.
     * @param args arguments for the constructor of the component.
    */
    template<typename C, typename... Args>
    C& addComponent(Args&&...);

    /// Get a component.
    /**
     * Attempting to retrieve a component that this node does not have will 
     * result in an exception.
     * 
     * @param <C> component type.
     */
    template<typename C>
    C& getComponent();

    /// Get a component, return a nullptr if not present.
    /**
     * @param <C> component type
     */
    template<typename C>
    C* tryGetComponent();

private:
    friend class Scene;
    
    // Construct an empty node, without a parent node
    Node(entt::registry&, const char*);

    void changeParent(Node*);

    entt::registry& _registry;
    entt::entity _entity;
    Node* _parent {nullptr};
    NodeList _children {};
    std::string _name;
};

// template function definitions

template<typename C, typename... Args>
C& Node::addComponent(Args&& ... args)
{
    if (tryGetComponent<C>())
        throw EngineRuntimeError("Node " + name() + " already has a component of this type.");
    
    return _registry.emplace<C>(_entity, std::forward<Args>(args)...);
}

template<typename C> 
C& Node::getComponent() 
{
    C* c =  _registry.try_get<C>(_entity);

    if (c)
        return c;
    else
        throw EngineRuntimeError("Node " + name() + "doesn't have a component of this type.");
}

template<typename C>
C* Node::tryGetComponent()
{
    return _registry.try_get<C>(_entity);
}

}//namespace folk

#endif//FOLK__NODE_HPP