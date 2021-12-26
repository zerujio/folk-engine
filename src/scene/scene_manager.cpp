#include "scene_manager.hpp"

#include "../core/engine_singleton.hpp"

#include "folk/script/script_component.hpp"
#include "folk/ai.hpp"

namespace Folk
{

static void onScriptConstruct(entt::registry& r, entt::entity e) {
    auto& script_component = r.get<ScriptComponent>(e);
    script_component.handle = entt::handle(r, e);
}

SceneManager::SceneManager() {
    registry().on_construct<ScriptComponent>().connect<onScriptConstruct>();
}

SceneManager::~SceneManager() 
try {
    // empty
} catch (...) {
    Log::error() << "Exception caught during scene destruction (possible resource leak?)";
    ENGINE.exception.handleException();
}

void SceneManager::updateScene(std::chrono::duration<float> delta) noexcept {
    // call scene update callback
    if (scene.updateCallback)
        try {
            scene.updateCallback(scene, delta.count());
        } catch (...) {
            ENGINE.exception.handleException();
        }

    // update scripts
    registry().view<ScriptComponent>().each([delta](ScriptComponent& script_component){
        try {
            script_component.script->update(delta);
        } catch (...) {
            ENGINE.exception.handleException();
        }
    });

    // update behavior trees
    registry().view<BehaviorTreeComponent>().each(
            [this, delta](entt::entity entity, BehaviorTreeComponent& bt_component) {
                try {
                    bt_component.bt->update({registry(), entity}, delta);
                } catch (...) {
                    ENGINE.exception.handleException();
                }
            });
}

} // namespace folk
