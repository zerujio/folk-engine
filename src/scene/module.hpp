#ifndef FOLK_SCENE__MODULE_HPP
#define FOLK_SCENE__MODULE_HPP

#include "folk/scene/scene.hpp"
#include "folk/scene/node.hpp"
#include "../utils/singleton.hpp"
#include "../utils/update_listener.hpp"

#include <entt/entt.hpp>

#define SCENE SceneModule::instance()

namespace Folk
{

FOLK_SINGLETON_CLASS_FINAL(SceneModule), public UpdateListener {
public:
    friend class EngineSingleton;
    
    SceneModule() = default;

    void update(Delta) override;

    // Scene scene {};

    entt::basic_registry<Node::Id> registry {};

    Scene scene {};
};
    
} // namespace folk

#endif // FOLK_SCENE__MODULE_HPP