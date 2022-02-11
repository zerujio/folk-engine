//
// Created by sergio on 09-02-22.
//

#include "folk/render/vertex_types.hpp"

namespace Folk {

const std::array<VertexAttribSpec, 2> PositionNormalVertex::vertex_attributes {
    // position
    VertexAttribSpec{ VertexAttribute::fromVectorType<Vec3>(false, VertexAttribute::Location::Position), 0 },
    // normal
    {VertexAttribute::fromVectorType<Vec3>(false, VertexAttribute::Location::Normal),
            offsetof(PositionNormalVertex, normal)}
};

const std::array<VertexAttribSpec, 3> PositionNormalTexCoordVertex::vertex_attributes {
    // position
    VertexAttribSpec{ VertexAttribute::fromVectorType<Vec3>(false, VertexAttribute::Location::Position), 0 },
    // normal
    {VertexAttribute::fromVectorType<Vec3>(false, VertexAttribute::Location::Normal),
            offsetof(PositionNormalTexCoordVertex, normal)},
    // texture coordinates
    {VertexAttribute::fromVectorType<Vec2>(false, VertexAttribute::Location::TexCoord),
            offsetof(PositionNormalTexCoordVertex, uv)}
};

} // namespace Folk