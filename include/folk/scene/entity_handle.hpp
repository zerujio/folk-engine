#ifndef FOLK_SCENE__NODE_HPP
#define FOLK_SCENE__NODE_HPP

#include "folk/core/error.hpp"
#include "folk/scene/transform_component.hpp"
#include "folk/scene/scene_graph_node.hpp"

#include <entt/entt.hpp>

#include <string>
#include <list>
#include <functional>
#include <optional>

namespace Folk {

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

    /// Asocia un componente de tipo C a esta entidad.
    /**
     * Cada entidad puede tener una única instancia de cada componente. Intentar
     * asociar un componente a una entidad que ya lo posee generará una excepción.
     * 
     * \param <C> Tipo del componente.
     * \param args Argumentos para el constructor.
    */
    template<typename C, typename... Args>
    decltype(auto) addComponent(Args&&...);

    /// Retorna una referencia al componente asociado a esta entidad.
    /**
     * \param <C>
     * \return Una instancia de std::optional que contiene un _handle_ al tipo de
     *         componente especificado si existe, o una vacía si no.
    */
    template<typename C>
    decltype(auto) getComponent();

    /// Quita un componente.
    /**
     * Intentar quitar un componente del que la entidad no es dueña constituye
     * comportamiento indefinido.
     * 
     * \param <C> tipo del componente.
     */
    template<typename C>
    void removeComponent();

    /// Quita un componente, si está presente.
    template<typename C>
    void removeComponentIfPresent();

private:
    SceneGraphNode& node() const;

    entt::handle m_handle;
};


// DEFINITIONS

template<typename C, typename... Args>
decltype(auto) EntityHandle::addComponent(Args&& ... args)
{
    static_assert(!std::is_same_v<C, SceneGraphNode>,
                  "Transform component can't be added.");

    if (m_handle.try_get<C>())
        throw EngineRuntimeError("Entity " + name() 
                                + " already has a component of type "
                                + C::type_name);
    
    m_handle.emplace<C>(std::forward<Args>(args)...);

    using P = typename C::ptr_type;
    return P(m_handle);
}

template<typename C> 
decltype(auto) EntityHandle::getComponent() 
{
    using P = typename C::ptr_type;

    C* c = m_handle.try_get<C>();

    if (c)
        return std::optional<P>(P(m_handle));
    else
        return std::optional<P>();
}

template<class C>
void EntityHandle::removeComponent()
{
    static_assert(std::is_same_v<C, SceneGraphNode>,
                  "Transform component can't be removed.");

    if (!m_handle.try_get<C>())
        throw EngineRuntimeError("Node " + name()
                                + " does not have a component of type "
                                + C::type_name + ": can't remove.");
    
    m_handle.remove<C>();
}

template<class C>
void EntityHandle::removeComponentIfPresent()
{
    m_handle.remove_if_exists<C>();
}

}//namespace folk

#endif//FOLK__NODE_HPP