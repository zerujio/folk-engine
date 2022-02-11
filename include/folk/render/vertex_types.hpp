#ifndef INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP
#define INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP

#include "vertex_attribute.hpp"
#include <array>

namespace Folk {

struct VertexAttribSpec final {
    VertexAttribute attribute;
    GLuint offset;
};

struct PositionVertex final {

    constexpr PositionVertex(float x, float y, float z) : position(x, y, z) {}

    Vec3 position {};

    static constexpr std::array<VertexAttribSpec, 1> vertex_attributes {
        VertexAttribute::fromVectorType<Vec3>(false, VertexAttribute::Location::Position), 0
    };
};

struct PositionNormalVertex final {
    Vec3 position {};
    Vec3 normal {};

    static const std::array<VertexAttribSpec, 2> vertex_attributes;
};

struct PositionNormalTexCoordVertex final {
    Vec3 position {};
    Vec3 normal {};
    Vec2 uv {};

    static const std::array<VertexAttribSpec, 3> vertex_attributes;
};

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP
