#ifndef INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP
#define INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP

#include "vertex_attribute.hpp"
#include <array>

namespace Folk {

struct PositionVertex final {

    constexpr PositionVertex(float x, float y, float z) : position(x, y, z) {}

    Vec3 position {};

    static constexpr std::array<VertexAttribSpec, 1> vertex_attributes {
            VertexAttribSpec(DefaultAttribIndex::Position, VertexAttribute::fromVectorType<Vec3>(false), /* offset */ 0)
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
    Vec2 tex_coord {};

    static const std::array<VertexAttribSpec, 3> vertex_attributes;
};

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP
