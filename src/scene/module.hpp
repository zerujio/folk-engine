#ifndef FOLK_SCENE__MODULE_HPP
#define FOLK_SCENE__MODULE_HPP

#include "folk/scene/scene.hpp"
#include "../utils/singleton.hpp"
#include "../utils/update_listener.hpp"

namespace Folk
{

FOLK_SINGLETON_CLASS_FINAL(SceneModule), public UpdateListener {
public:
    friend class EngineSingleton;
    
    SceneModule() = default;

    void update(Delta) override;

    Scene scene {};
};
    
} // namespace folk


#endif // FOLK_SCENE__MODULE_HPP