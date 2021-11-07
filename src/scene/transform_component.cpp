#include "folk/scene/transform_component.hpp"
#include "folk/scene/node.hpp"

#include "node_template_functions.hpp"

#include "bx/math.h"

namespace Folk
{

// Explicit instantiation of Node template functions

template TransformComponent& Node::addComponent();

template TransformComponent& Node::getComponent();

template TransformComponent* Node::tryGetComponent();

const Vec3f& TransformComponent::position() const {
    return m_position;
}

void TransformComponent::position(const Vec3f& vec3) {
    m_position = vec3;

    bx::mtxTranslate(m_position_mtx, vec3.x, vec3.y, vec3.z);

    updateLocal();
}

const Vec3f& TransformComponent::rotation() const {
    return m_rotation;
}

void TransformComponent::rotation(const Vec3f& vec3) {
    m_rotation = vec3;

    float tmp0[16];
    bx::mtxRotateY(tmp0, vec3.y);
    bx::mtxRotateZ(m_rotation_mtx, vec3.z);
    float tmp1[16];
    bx::mtxMul(tmp1, tmp0, m_rotation_mtx);
    bx::mtxRotateX(tmp0, vec3.x);
    bx::mtxMul(m_rotation_mtx, tmp0, tmp1);

    updateLocal();
}

const Vec3f& TransformComponent::scale() const {
    return m_scale;
}

void TransformComponent::scale(const Vec3f& scale) {
    m_scale = scale;

    bx::mtxScale(m_scale_mtx, scale.x, scale.y, scale.z);

    updateLocal();
}

const TransformComponent::Matrix& TransformComponent::localMatrix() const {
    return m_local_mtx;
}

TransformComponent::Matrix::Matrix() {
    bx::mtxIdentity(m_arr);
}

void TransformComponent::updateLocal() {
    float tmp[16];
    bx::mtxMul(tmp, m_rotation_mtx, m_position_mtx);
    bx::mtxMul(m_local_mtx, tmp, m_scale_mtx);
}

} // namespace Folk
