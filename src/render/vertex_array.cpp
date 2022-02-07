//
// Created by sergio on 05-02-22.
//

#include "folk/render/vertex_array.hpp"

namespace Folk {

const std::array<VertexAttribute, 2> PositionColorVertex::vertex_attributes {
        makeVertexAttribute<Vec3>(false, 0),
        {VertexAttributeType::UByte, VertexAttributeSize::XYZW, true, offsetof(PositionColorVertex, color)}
};

void VertexArray::bind() const {
    m_vao.bind();
}

void VertexArray::unbind() {
    gl::VertexArrayHandle::unbind();
}

void VertexArray::bufferData(const void *data, GLsizei size, gl::BufferHandle buffer, gl::BufferTarget target) {
    buffer.bind(target);
    gl::call::slow(glBufferData)(static_cast<GLenum>(target), size, data, GL_STATIC_DRAW);
}

void VertexArray::addVertexAttribute(int index, const VertexAttribute &attribute, GLsizei stride)
{
    gl::call::fast(glVertexAttribPointer)(index, static_cast<GLint>(attribute.size), static_cast<GLenum>(attribute.type),
                                          attribute.normalize, stride, reinterpret_cast<void*>(attribute.offset));
    gl::call::fast(glEnableVertexAttribArray)(index);
}

} // namespace Folk