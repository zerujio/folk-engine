#include "module.hpp"
#include "../core/engine_singleton.hpp"

namespace Folk
{

SceneModule::SceneModule()
{}

void SceneModule::update(Delta dt) {
    if (scene.updateCallback)
        scene.updateCallback(scene, dt.count());
}

} // namespace folk
