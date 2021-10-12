#include "module.hpp"

namespace folk
{

void SceneModule::update(Delta dt) {
    if (scene.updateCallback)
        scene.updateCallback(scene, dt.count());
}

} // namespace folk
