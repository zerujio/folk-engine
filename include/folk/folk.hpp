#ifndef FOLK_HPP
#define FOLK_HPP

#include "folk/scene.hpp"

namespace folk
{

/* Called before engine module initialization. Allows global engine settings to
be configured before the first scene is loaded. */
void engineInit();

/* This function is called with an empty scene as argument. This is the scene
the engine is currently playing.

All engine modules have been initialized at this point. */
void sceneInit(Scene&);

}//namespace folk

#endif//FOLK_HPP