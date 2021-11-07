#ifndef FOLK_SCENE__NODE_HPP
#define FOLK_SCENE__NODE_HPP

#include "folk/core/error.hpp"

#include <string>
#include <vector>
#include <functional>

namespace Folk {

/// \~spanish Nodo del grafo de escena. \~english A scene graph node.
class Node {
public:
    Node(const Node&) = delete;
    Node& operator= (const Node&) = delete;
    ~Node();

    /// \~spanish \brief Añade un nodo como hijo, lo que cambiará el padre de dicho nodo a `this`.
    /// \~english \brief Add node as child. This will change said nodes' parent to *this.
    void addChild(Node& n);

    /// \~spanish \brief Añade un nodo vacío nuevo como hijo y retorna una referencia.
    /// \~english \brief Add a new, empty node as child of this node and return a reference.
    Node& createChild(const char*);
    Node& createChild();

    /// \~spanish Busca un nodo por su nombre. \~english Find a child by name.
    Node& getChild(const char* name);

    /// \~spanish Destruye este nodo. \~english Destroy this node.
    void destroy();

    using NodeList = std::vector<Node*>;

    /// \~spanish \brief Retorna un vector de punteros a los hijos de este nodo.
    /// \~english Return a list of pointers to this node's children.
    NodeList const& getChildren();

    /// \~spanish Retorna el padre de este nodo. \~english Retrieve this node's parent.
    Node& getParent();

    std::string& name() {return _name;}

    /// \~spanish Añade un componente a este nodo. \~english Add a component to this node.
    /**
     * \~spanish
     * A cada nodo se le puede asociar una sola instancia de cada componente. 
     * Intentar añadir un componente a un nodo que ya lo posee generará una
     * excepción.
     * 
     * \param C la clase del componente.
     * \param args argumentos que pasar al constructor del componente.
     * 
     * \~english
     * Adding a component to a node that already has said component will result
     * in a an exception.
     * 
     * \param <C> the type of component.
     * \param args arguments for the constructor of the component.
    */
    template<typename C, typename... Args>
    C& addComponent(Args&&...);

    /// \~spanish Obtiene un componente. \~english Get a component.
    /**
     * \~spanish
     * Intentar obtener un componente que este nodo no posee generará una excepción.
     * 
     * Un puntero o referencia a un componente no es estable, es decir, no hay
     * garantía de que siga siendo válido entre un cuadro y el siguiente. 
     * 
     * \param C tipo del componente.
     * 
     * \~english
     * Attempting to retrieve a component that this node does not have will 
     * result in an exception.
     * 
     * \param <C> component type.
     */
    template<typename C>
    C& getComponent();

    /// \~spanish \brief Obtiene un componente, retorna un puntero nulo si no está presente.
    /// \~english \brief Get a component, return a nullptr if not present.
    /**
     * \~spanish
     * \param C tipo del componente.
     * 
     * \~english
     * \param <C> component type
     */
    template<typename C>
    C* tryGetComponent();

    /// Quita un componente.
    /**
     * \param C tipo del componente.
     */
    template<typename C>
    void removeComponent();

    /// Quita un componente, si existe.
    /**
     * \param C tipo del componente.
     * \return si el componente fue quitado o no.
     */
    template<typename C>
    bool tryRemoveComponent();

    enum class Id : std::uint32_t {}; 

private:
    friend class Scene;
    
    // Construye un nodo vacío, sin nodo padre.
    Node(const char*);

    void changeParent(Node*);
    void onParentChange();

    Id _id;
    Node* _parent {nullptr};
    NodeList _children {};
    std::string _name;
};

// DEFINITIONS

template<typename C, typename... Args>
C& Node::addComponent(Args&& ... args)
{
    if (C::getComponent(_id))
        throw EngineRuntimeError("Node " + name() 
                                + " already has a component of type "
                                + C::type_name);
    
    return C::emplaceComponent(_id, std::forward<Args>(args)...);
}

template<typename C> 
C& Node::getComponent() 
{
    C* c = C::getComponent(_id);

    if (c)
        return *c;
    else
        throw EngineRuntimeError("Node " + name()
                                + "doesn't have a component of type "
                                + C::type_name);
}

template<typename C>
C* Node::tryGetComponent()
{
    return C::getComponent(_id);
}

template<class C>
void Node::removeComponent() 
{
    if (!C::removeComponent(_id)) {
        throw EngineRuntimeError("Node " + name()
                                + " does not have a component of type "
                                + C::type_name + ": can't remove.");
    }
}

template<class C>
bool Node::tryRemoveComponent()
{
    return C::removeComponent(_id);
}

}//namespace folk

#endif//FOLK__NODE_HPP