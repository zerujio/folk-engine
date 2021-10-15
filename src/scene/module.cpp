#include "module.hpp"
#include "../core/engine_singleton.hpp"

namespace Folk
{

SceneModule::SceneModule() 
    : monitor_id(ENGINE.perf_monitor.addItem("Scene update"))
{}

void SceneModule::update(Delta dt) {
    ENGINE.perf_monitor.start(monitor_id);

    if (scene.updateCallback)
        scene.updateCallback(scene, dt.count());

    ENGINE.perf_monitor.stop(monitor_id);
}

} // namespace folk
