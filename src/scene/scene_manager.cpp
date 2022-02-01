#include "scene_manager.hpp"

#include "../core/engine.hpp"

#include "folk/script/script_component.hpp"
#include "folk/ai.hpp"

namespace Folk
{

static void onScriptConstruct(entt::registry& r, entt::entity e) {
    auto& script_component = r.get<ScriptComponent>(e);
    script_component.handle = entt::handle(r, e);
}

SceneManager::SceneManager() noexcept {
    registry().on_construct<ScriptComponent>().connect<onScriptConstruct>();
}

SceneManager::~SceneManager() 
try {
    // empty
} catch (...) {
    Log::error() << "Exception caught during scene destruction (possible resource leak?)";
}

void SceneManager::updateScene(InputEventQueue& input_manager, const ExceptionHandler &exception_handler, std::chrono::duration<float> delta) noexcept {
    // call input callbacks
    input_manager.update(m_scene.m_input_registry, exception_handler);

    // call scene update callback
    if (m_scene.updateCallback)
        try {
            m_scene.updateCallback(m_scene, delta.count());
        } catch (...) {
            exception_handler.catchException();
        }

    // update scripts
    registry().view<ScriptComponent>().each([exception_handler, delta](ScriptComponent& script_component){
        try {
            script_component.script->update(delta);
        } catch (...) {
            exception_handler.catchException();
        }
    });

    // update behavior trees
    registry().view<BehaviorTreeComponent>().each(
            [this, exception_handler, delta](entt::entity entity, BehaviorTreeComponent& bt_component) {
                try {
                    bt_component.bt->update({registry(), entity}, delta);
                } catch (...) {
                    exception_handler.catchException();
                }
            });
}

} // namespace folk
