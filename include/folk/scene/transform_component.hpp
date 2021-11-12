#ifndef FOLK_SCENE__TRANSFORM_COMPONENT_HPP
#define FOLK_SCENE__TRANSFORM_COMPONENT_HPP

#include "folk/math/vector.hpp"
#include "folk/math/matrix.hpp"

#include "folk/scene/entity_handle.hpp"

namespace Folk
{

/// Determina la posición y orientación de un objeto (Node) en la escena.
/**
 * Todos los nodos se crean con una componente Transform, y esta no puede ser
 * quitada.
*/
class TransformComponent {

public: 
    static constexpr const char* type_name = "Transform";

    TransformComponent();

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

    static TransformComponent& emplaceComponent(const entt::handle);
    static TransformComponent* getComponent(const entt::handle);
    static bool removeComponent(const entt::handle);

private:
    Vec3f m_position {0, 0, 0};
    Vec3f m_rotation {0, 0, 0};
    Vec3f m_scale    {1, 1, 1};
    
    Matrix4f m_transform_mtx;

    entt::entity m_parent_id;

    bool m_modified;

    void updateTransform();

    friend class EntityHandle;
};



} // namespace Folk


#endif // FOLK_SCENE__TRANSFORM_COMPONENT_HPP