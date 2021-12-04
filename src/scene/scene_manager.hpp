#ifndef FOLK_SCENE__MODULE_HPP
#define FOLK_SCENE__MODULE_HPP

#include "folk/scene/scene.hpp"
#include "folk/scene/entity_handle.hpp"

#include "../core/module.hpp"

#include <entt/entt.hpp>

#define SCENE SceneManager::instance()

namespace Folk
{

FOLK_ENGINE_UPDATEABLE_MODULE(SceneManager) {
public:
    friend class EngineSingleton;
    
    SceneManager() = default;
    ~SceneManager();

    void update(Delta) override;

    const char* name() const override {return "Scene update";}

    Scene scene {};
    
private:
    int monitor_id;

    entt::registry& registry() {
        return scene.m_registry;
    }
};
    
} // namespace folk

#endif // FOLK_SCENE__MODULE_HPP