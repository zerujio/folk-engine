#include "module.hpp"

namespace Folk
{

void SceneModule::update(Delta dt) {
    if (scene.updateCallback)
        scene.updateCallback(scene, dt.count());
}

} // namespace folk
