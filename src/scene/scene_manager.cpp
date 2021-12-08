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
    ENGINE.exception.handleException();
}

void SceneManager::updateScene(std::chrono::duration<double> delta) {
    if (scene.updateCallback)
        scene.updateCallback(scene, delta.count());
}

} // namespace folk
