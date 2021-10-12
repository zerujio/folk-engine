#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "../utils/singleton.hpp"
#include "../utils/update_listener.hpp"

namespace folk {

FOLK_SINGLETON_CLASS_FINAL(RenderModule), public UpdateListener {
private:
    friend class EngineSingleton;

    RenderModule();

    void update(Delta) override;
};

} // namespace folk

#endif//FOLK_RENDER__MODULE_HPP