#ifndef FOLK_SCENE__MODULE_HPP
#define FOLK_SCENE__MODULE_HPP

#include "folk/scene/scene.hpp"
#include "folk/scene/entity_handle.hpp"

#include <entt/entt.hpp>

#include <chrono>

#define SCENE SceneManager::instance()

namespace Folk
{

class SceneManager final {

public:
    friend class EngineSingleton;
    
    SceneManager() = default;
    ~SceneManager();

    const char* name() const {return "Scene update";}

    void updateScene(std::chrono::duration<double>);

    const entt::registry& registry() const {
        return scene.m_registry;
    }

    entt::registry& registry() {
        return scene.m_registry;
    }

    entt::entity camera() const {
        return scene.m_camera;
    }

    entt::entity root() const {
        return scene.m_root;
    }
    
private:
    int monitor_id;
    Scene scene {};
};
    
} // namespace folk

#endif // FOLK_SCENE__MODULE_HPP