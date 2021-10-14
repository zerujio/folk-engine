#ifndef FOLK_SCENE__NODE_TEMPLATE_FUNCTIONS_HPP
#define FOLK_SCENE__NODE_TEMPLATE_FUNCTIONS_HPP

#include "folk/scene/node.hpp"
#include "module.hpp"

#include <entt/entt.hpp>

namespace Folk
{

// template function definitions

template<typename C, typename... Args>
C& Node::addComponent(Args&& ... args)
{
    if (tryGetComponent<C>())
        throw EngineRuntimeError("Node " + name() + 
                                " already has a component of this type.");
    
    return SCENE.registry.emplace<C>(_id, std::forward<Args>(args)...);
}

template<typename C> 
C& Node::getComponent() 
{
    C* c =  SCENE.registry.try_get<C>(_id);

    if (c)
        return *c;
    else
        throw EngineRuntimeError("Node " + name() + 
                                "doesn't have a component of this type.");
}

template<typename C>
C* Node::tryGetComponent()
{
    return SCENE.registry.try_get<C>(_id);
}

} // namespace Folk


#endif // FOLK_SCENE__NODE_TEMPLATE_FUNCTIONS_HPP