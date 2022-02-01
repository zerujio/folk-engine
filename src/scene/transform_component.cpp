#include "folk/scene/transform_component.hpp"
#include "folk/scene/entity_handle.hpp"
#include "folk/scene/scene_graph_node.hpp"

namespace Folk
{

// Explicit instantiation of Node template functions

const Vec3& TransformPtr::position() const {
    return ref.m_transform.position;
}

void TransformPtr::position(const Vec3& vec3) {
    ref.m_transform.position = vec3;
    ref.invalidateMtxCache();
}

const Vec3& TransformPtr::rotation() const {
    return ref.m_transform.rotation;
}

void TransformPtr::rotation(const Vec3& vec3) {
    ref.m_transform.rotation = vec3;
    ref.invalidateMtxCache();
}

const Vec3& TransformPtr::scale() const {
    return ref.m_transform.scale;
}

void TransformPtr::scale(const Vec3& scale) {
    ref.m_transform.scale = scale;
    ref.invalidateMtxCache();
}

const Mat4& TransformPtr::transformMatrix() {
    return ref.transformMatrix();
}

} // namespace Folk
