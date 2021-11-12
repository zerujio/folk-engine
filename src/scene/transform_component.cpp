#include "folk/scene/transform_component.hpp"
#include "folk/scene/entity_handle.hpp"

#include "bx/math.h"

namespace Folk
{

// Explicit instantiation of Node template functions

TransformComponent& TransformComponent::emplaceComponent(const entt::handle handle) {
    return handle.emplace<TransformComponent>();
}

TransformComponent* TransformComponent::getComponent(const entt::handle handle) {
    return handle.try_get<TransformComponent>();
}

bool TransformComponent::removeComponent(const entt::handle handle) {
    return handle.remove<TransformComponent>();
}

const Vec3f& TransformComponent::position() const {
    return m_position;
}

void TransformComponent::position(const Vec3f& vec3) {
    m_position = vec3;

    m_modified = true;
}

const Vec3f& TransformComponent::rotation() const {
    return m_rotation;
}

void TransformComponent::rotation(const Vec3f& vec3) {
    m_rotation = vec3;

    m_modified = true;
}

const Vec3f& TransformComponent::scale() const {
    return m_scale;
}

void TransformComponent::scale(const Vec3f& scale) {
    m_scale = scale;

    m_modified = true;
}

const Matrix4f& TransformComponent::transformMatrix() {
    if (m_modified) 
        updateTransform();
    
    return m_transform_mtx;
}

void TransformComponent::updateTransform() {
    float a[16], b[16], c[16];
    
    // scale
    bx::mtxScale(a, m_scale.x, m_scale.y, m_scale.z);

    // rotation
    bx::mtxRotateY(b, m_rotation.y);
    bx::mtxMul(c, a, b);

    bx::mtxRotateZ(a, m_rotation.z);
    bx::mtxMul(b, c, a);

    bx::mtxRotateX(c, m_rotation.x);
    bx::mtxMul(a, b, c);

    // position
    bx::mtxTranslate(b, m_position.x, m_position.y, m_position.z);

    bx::mtxMul(m_transform_mtx, a, b);

    m_modified = false;
}

TransformComponent::TransformComponent() : m_parent_id(entt::null) {
    bx::mtxIdentity(m_transform_mtx);
}

} // namespace Folk
