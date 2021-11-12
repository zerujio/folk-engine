#ifndef FOLK_SCENE__MODULE_HPP
#define FOLK_SCENE__MODULE_HPP

#include "folk/scene/scene.hpp"
#include "folk/scene/entity_handle.hpp"

#include "../core/module.hpp"

#include <entt/entt.hpp>

#define SCENE SceneModule::instance()

namespace Folk
{

FOLK_ENGINE_UPDATEABLE_MODULE(SceneModule) {
public:
    friend class EngineSingleton;
    
    SceneModule();

    void update(Delta) override;

    const char* name() const override {return "Scene update";}

    Scene scene {};
    
private:
    int monitor_id;
};
    
} // namespace folk

#endif // FOLK_SCENE__MODULE_HPP