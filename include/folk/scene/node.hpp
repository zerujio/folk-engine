#ifndef FOLK_SCENE__NODE_HPP
#define FOLK_SCENE__NODE_HPP

#include "folk/core/error.hpp"

#include <string>
#include <vector>

namespace Folk {

/// A scene graph node.
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
    Node& createChild(const char*);
    Node& createChild();

    /// Find a child by name.
    /**
     * @param name name of the child to retrieve.
     */
    Node& getChild(const char* name);

    /// Destroy this node.
    void destroy();

    using NodeList = std::vector<Node*>;

    /// Return a list of pointers to this node's children.
    NodeList const& getChildren();

    /// Retrieve this node's parent.
    Node& getParent();

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

    enum class Id : unsigned int {}; 

private:
    friend class Scene;
    
    // Construct an empty node, without a parent node
    Node(const char*);

    void changeParent(Node*);

    Id _id;
    Node* _parent {nullptr};
    NodeList _children {};
    std::string _name;
};

}//namespace folk

#endif//FOLK__NODE_HPP