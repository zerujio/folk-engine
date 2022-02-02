#ifndef FOLK_HPP
#define FOLK_HPP

#include "scene.hpp"
#include "folk/scene/entity_handle.hpp"
#include "folk/core/game.hpp"

/// folk engine namespace
namespace Folk
{

/// \~spanish \brief Se invoca durante la inicialización del engine para permitir la configuración de ciertas variables globales.
/// \~english \brief Called before engine initialization, allows configuration of certain settings.
/** 
 * \see sceneInit()
 */
void engineInit();

/// \~spanish \brief Se invoca después de que el engine se ha inicializado y la escena ha sido instanciada.
/// \~english \brief Called after engine initialization and scene instantiation.
/**
 * \~spanish
 * Esta función es para añadir elementos a la escena.
 * \param scene La escena actual (en ejecución).
 * 
 * \~english
 * Use this function to add elements to the scene.
 * 
 * \param scene current scene.
 * 
 * \~
 * \see engineInit()
 */
void sceneInit(Scene& scene);

}//namespace folk

#endif//FOLK_HPP