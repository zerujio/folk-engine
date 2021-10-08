#ifndef FOLK_HPP
#define FOLK_HPP

#include "folk/scene.hpp"

/// folk engine namespace
namespace folk
{

/// Called after engine initialization, but before scene initialization.
/** 
 * Use this callback to set global engine settings before a scene is 
 * instantiated.
 * 
 * @see sceneInit()
 */
void engineInit();

/// Called after engine initialization and scene instantiation.
/**
 * Use this function to add elements to the scene.
 * 
 * @param scene an empty [Scene](@ref Scene).
 * @see engineInit()
 */
void sceneInit(Scene& scene);

}//namespace folk

#endif//FOLK_HPP