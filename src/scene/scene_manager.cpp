#include "scene_manager.hpp"

#include "../core/engine_singleton.hpp"

namespace Folk
{

SceneManager::~SceneManager() 
try {
    // empty
} catch (...) {
    ENGINE.log.begin(Log::Level::ERROR) 
        << "Exception caught during scene destruction (possible resource leak?)";
    ENGINE.exception.handle();
}

void SceneManager::update(Delta dt) {
    if (scene.updateCallback)
        scene.updateCallback(scene, dt.count());
}

} // namespace folk
