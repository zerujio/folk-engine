#ifndef FOLK_SCENE__TRANSFORM_COMPONENT_HPP
#define FOLK_SCENE__TRANSFORM_COMPONENT_HPP

#include "folk/math/vector.hpp"
#include "folk/math/matrix.hpp"

#include "folk/scene/entity_handle.hpp"
#include "folk/scene/component_ptr.hpp"
#include "folk/scene/scene_graph_node.hpp"

namespace Folk
{

/// Determina la posición y orientación de una entidad en la escena.
/**
 * Todos los nodos se crean con una componente Transform, y esta no puede ser
 * quitada.
*/
class TransformPtr : public ComponentPtr<SceneGraphNode> {

public: 
    static constexpr const char* type_name = "Transform";

    using ComponentPtr::ComponentPtr;

    /// Consulta la posición.
    const Vec3f& position() const;

    /// Modifica la posición;
    void position(const Vec3f&);

    /// Consulta la rotación
    const Vec3f& rotation() const;
    
    /// Modifica la rotación.
    void rotation(const Vec3f&);

    /// Consulta la escala.
    const Vec3f& scale() const;

    /// Modifica la escala;
    void scale(const Vec3f&);

    /// Matriz de transformación local.
    const Matrix4f& transformMatrix();
};

using TransformComponent = SceneGraphNode;

} // namespace Folk


#endif // FOLK_SCENE__TRANSFORM_COMPONENT_HPP