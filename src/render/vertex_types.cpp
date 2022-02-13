//
// Created by sergio on 09-02-22.
//

#include "folk/render/vertex_types.hpp"

namespace Folk {

const std::array<VertexAttribSpec, 2> PositionNormalVertex::vertex_attributes {
    // position
    VertexAttribSpec{DefaultAttribIndex::Position, VertexAttribute::fromVectorType<Vec3>(false), 0 },
    // normal
    {DefaultAttribIndex::Normal, VertexAttribute::fromVectorType<Vec3>(false), offsetof(PositionNormalVertex, normal)}
};

const std::array<VertexAttribSpec, 3> PositionNormalTexCoordVertex::vertex_attributes {
    // position
    VertexAttribSpec{DefaultAttribIndex::Position, VertexAttribute::fromVectorType<Vec3>(false), 0 },
    // normal
    {DefaultAttribIndex::Normal, VertexAttribute::fromVectorType<Vec3>(false), offsetof(PositionNormalTexCoordVertex, normal)},
    // texture coordinates
    {DefaultAttribIndex::TexCoord, VertexAttribute::fromVectorType<Vec2>(false), offsetof(PositionNormalTexCoordVertex, tex_coord)}
};

} // namespace Folk