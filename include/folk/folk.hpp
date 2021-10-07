#ifndef FOLK_HPP
#define FOLK_HPP

#include "folk/scene.hpp"

namespace folk
{

/// Se invoca luego de que todos los módulos del motor han sido inicializados.
/** 
 * Permite configurar opciones globales del motor antes de que se inicialize la 
 * primera escena.
 * 
 * @see sceneInit()
 */
void engineInit();

/// Se invoca luego de que se ha instanciado una escena vacía.
/**
 * En esta función se deben añadir elementos a la escena.
 * 
 * @param scene escena vacía
 * @see engineInit()
 */
void sceneInit(Scene& scene);

}//namespace folk

#endif//FOLK_HPP