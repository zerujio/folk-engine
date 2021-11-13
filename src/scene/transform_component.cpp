#include "folk/scene/transform_component.hpp"
#include "folk/scene/entity_handle.hpp"
#include "folk/scene/scene_graph_node.hpp"

#include "bx/math.h"

namespace Folk
{

// Explicit instantiation of Node template functions

const Vec3f& TransformPtr::position() const {
    return ref.m_transform.position;
}

void TransformPtr::position(const Vec3f& vec3) {
    ref.m_transform.position = vec3;
    ref.invalidateMtxCache();
}

const Vec3f& TransformPtr::rotation() const {
    return ref.m_transform.rotation;
}

void TransformPtr::rotation(const Vec3f& vec3) {
    ref.m_transform.rotation = vec3;
    ref.invalidateMtxCache();
}

const Vec3f& TransformPtr::scale() const {
    return ref.m_transform.scale;
}

void TransformPtr::scale(const Vec3f& scale) {
    ref.m_transform.scale = scale;
    ref.invalidateMtxCache();
}

const Matrix4f& TransformPtr::transformMatrix() {
    return ref.transformMatrix();
}

} // namespace Folk
