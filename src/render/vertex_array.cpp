//
// Created by sergio on 05-02-22.
//

#include "folk/render/vertex_array.hpp"

namespace Folk {


void VertexArray::bind() const {
    m_vao.bind();
}

void VertexArray::unbind() {
    gl::VertexArrayHandle::unbind();
}

void VertexArray::writeBuffer(const void *data, GLsizei size) {
    gl::call::slow(glBufferData)(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexArray::addVertexAttribute(int index, const VertexAttribute &attribute, GLsizei stride, GLsizei offset)
{
    gl::call::fast(glVertexAttribPointer)(index, static_cast<GLint>(attribute.size), static_cast<GLenum>(attribute.type),
                                          attribute.norm, stride, reinterpret_cast<void*>(offset));
    gl::call::fast(glEnableVertexAttribArray)(index);
}

} // namespace Folk