#include "folk/core/engine.hpp"
#include "../window/module.hpp"
#include "engine_singleton.hpp"

namespace Folk::Engine {

void exit() 
{
    ENGINE.exit();
}

void setWindowTitle(const char* text) 
{
    ENGINE.window.setWindowTitle(text);
}

} // namespace folk::engine