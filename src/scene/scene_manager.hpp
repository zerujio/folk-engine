#ifndef FOLK_SCENE__MODULE_HPP
#define FOLK_SCENE__MODULE_HPP

#include "folk/scene.hpp"
#include "folk/scene/entity_handle.hpp"
#include "folk/utils/exception_handler.hpp"
#include "folk/input/input_event_queue.hpp"

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

    void updateScene(InputEventQueue& event_queue, const ExceptionHandler &exception_handler, std::chrono::duration<float> delta) noexcept;

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

    const Scene& scene() const {
        return m_scene;
    }

    Scene& scene() {
        return m_scene;
    }

private:
    Scene m_scene {};
};
    
} // namespace folk

#endif // FOLK_SCENE__MODULE_HPP