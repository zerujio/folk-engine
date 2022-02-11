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

void VertexArray::bufferData(const void *data, GLsizei size, gl::BufferHandle buffer, gl::BufferTarget target) {
    buffer.bind(target);
    gl::call::slow(glBufferData)(static_cast<GLenum>(target), size, data, GL_STATIC_DRAW);
}

void VertexArray::addVertexAttribute(const VertexAttribute &attribute, GLsizei stride, GLuint offset)
{
    gl::call::fast(glVertexAttribPointer)(
            attribute.location,
            static_cast<GLint>(attribute.count),
            static_cast<GLenum>(attribute.type.gl_enum),
            attribute.normalize,
            stride,
            reinterpret_cast<void*>(offset));
    gl::call::fast(glEnableVertexAttribArray)(attribute.location);
}

} // namespace Folk