#ifndef FOLK_HPP
#define FOLK_HPP

#include "folk/scene/scene.hpp"
#include "folk/core/engine.hpp"

/// folk engine namespace
namespace folk
{

/// Called before engine initialization, allows configuration of certain settings.
/** 
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