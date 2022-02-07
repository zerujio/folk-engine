//
// Created by sergio on 06-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP
#define INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP

namespace Folk {

struct PositionVertex final {
    Vec3 position {};

    static constexpr std::array<VertexAttribute, 1> vertex_attributes {
            makeVertexAttribute<Vec3>(false, 0)
    };
};

using Color = glm::u8vec4;
struct PositionColorVertex final {
    Vec3 position {};
    Color color {};

    static const std::array<VertexAttribute, 2> vertex_attributes;
    // vertex_attributes[0] = {VertexAttributeType::Float, VertexAttributeSize::XYZ, false, 0};
    // vertex_attributes[1] = {VertexAttributeType::UByte, VertexAttributeSize::XYZW, true, offsetof(PositionColorVertex, color)}:
};

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__VERTEX_TYPES_HPP
