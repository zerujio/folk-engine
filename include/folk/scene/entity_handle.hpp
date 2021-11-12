#ifndef FOLK_SCENE__NODE_HPP
#define FOLK_SCENE__NODE_HPP

#include "folk/core/error.hpp"

#include <entt/entt.hpp>

#include <string>
#include <list>
#include <functional>
#include <optional>

namespace Folk {

struct SceneGraphNode;

/// \~spanish Nodo del grafo de escena. \~english A scene graph node.
class EntityHandle {
public:
    /// (uso interno) Crea una referencia a una entidad.
    EntityHandle(entt::handle h) : m_handle(h) {}
    EntityHandle(entt::registry &r, entt::entity e) : m_handle(r, e) {}

    /// El nombre de esta entidad
    const std::string& name() const;

    /// Destruye esta entidad y todas las entidades hijas.
    void destroy();

    /// Consulta si la referencia es válida (i.e. si la entidad referenciada existe).
    bool valid() const;

    /// Añade otra entidad como hija en el grafo de escena.
    void addChild(const EntityHandle& n) const;

    /// Crea una nueva entidad y la añade como hija en el grafo de escena.
    /**
     * \param name Nombre de la nueva entidad.
    */
    EntityHandle createChild(const char*) const;
    EntityHandle createChild() const;

    /// Busca una entidad hija por su nombre.
    /**
     * Si más de una entidad hija tiene el mismo nombre no está definido cuál
     * será retornada.
    */
    std::optional<EntityHandle> getChild(const char* name) const;

    using HandleList = std::list<EntityHandle>;

    /// Crea una lista de referencias a las entidades hijas.
    HandleList getChildren() const;

    /// Retorna la entidad madre en el grafo de escena.
    std::optional<EntityHandle> getParent() const;

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

private:
    SceneGraphNode& node() const;

    entt::handle m_handle;
};

// DEFINITIONS

template<typename C, typename... Args>
C& EntityHandle::addComponent(Args&& ... args)
{
    if (C::getComponent(m_handle))
        throw EngineRuntimeError("Node " + name() 
                                + " already has a component of type "
                                + C::type_name);
    
    return C::emplaceComponent(m_handle, std::forward<Args>(args)...);
}

template<typename C> 
C& EntityHandle::getComponent() 
{
    C* c = C::getComponent(m_handle);

    if (c)
        return *c;
    else
        throw EngineRuntimeError("Node " + name()
                                + "doesn't have a component of type "
                                + C::type_name);
}

template<typename C>
C* EntityHandle::tryGetComponent()
{
    return C::getComponent(m_handle);
}

template<class C>
void EntityHandle::removeComponent() 
{
    if (!C::removeComponent(m_handle)) {
        throw EngineRuntimeError("Node " + name()
                                + " does not have a component of type "
                                + C::type_name + ": can't remove.");
    }
}

template<class C>
bool EntityHandle::tryRemoveComponent()
{
    return C::removeComponent(m_handle);
}

}//namespace folk

#endif//FOLK__NODE_HPP