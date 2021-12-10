//
// Created by sergio on 08-12-21.
//

#ifndef FOLK_SCRIPT__SCRIPT_HPP
#define FOLK_SCRIPT__SCRIPT_HPP

#include "folk/scene/entity_handle.hpp"

#include <chrono>

namespace Folk {

/// Un script que puede ser añadido a una entidad mediante el ScriptComponent.
/**
 * Los scripts definidos por el usuario deben heredar de esta clase. Se pueden implementar constructores y destructores
 * definidos por el usuario.
 * */
class Script {
protected:
    /// La entidad a la que este script está asociado.
    EntityHandle this_entity;

public:
    explicit Script(EntityHandle entity) : this_entity(entity) {}
    virtual ~Script() = default;

    /// Función de actualización, se invoca cada cuadro.
    /**
     * @param delta el tiempo transcurrido desde el último cuadro.
     * */
    virtual void update(std::chrono::duration<float> delta) = 0;
};

}

#endif //FOLK_SCRIPT__SCRIPT_HPP
