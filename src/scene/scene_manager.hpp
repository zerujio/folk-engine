#ifndef FOLK_SCENE__MODULE_HPP
#define FOLK_SCENE__MODULE_HPP

#include "folk/scene.hpp"
#include "folk/scene/entity_handle.hpp"
#include "folk/core/exception_handler.hpp"
#include "../input/input_event_queue.hpp"

#include <entt/entt.hpp>

#include <chrono>

#define SCENE SceneManager::instance()

namespace Folk
{

class SceneManager final {

public:
    friend class EngineSingleton;
    
    SceneManager() noexcept;
    ~SceneManager();

    static const char* name() {return "Scene update";}

    void updateScene(InputEventQueue& input_manager, const ExceptionHandler &exception_handler, std::chrono::duration<float> delta) noexcept;

    const entt::registry& registry() const {
        return m_scene.m_entity_registry;
    }

    entt::registry& registry() {
        return m_scene.m_entity_registry;
    }

    entt::entity camera() const {
        return m_scene.m_camera;
    }

    entt::entity root() const {
        return m_scene.m_root;
    }

    const Scene &getScene() const {
        return m_scene;
    }

private:
    Scene m_scene {};
};
    
} // namespace folk

#endif // FOLK_SCENE__MODULE_HPP