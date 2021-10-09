#ifndef FOLK__NODE_HPP
#define FOLK__NODE_HPP

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

}//namespace folk

#endif//FOLK__NODE_HPP