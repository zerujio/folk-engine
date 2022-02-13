#include "folk/render/gl_buffer.hpp"

namespace Folk::gl {

GLboolean isBuffer(GLuint id) {
    return glIsBuffer(id);
}

void Buffer::bind(BufferTarget target) const {
    Call::fast(glBindBuffer)(static_cast<GLenum>(target), id());
}

void Buffer::unbind(BufferTarget target) {
    Call::fast(glBindBuffer)(static_cast<GLenum>(target), 0);
}

void Buffer::data(BufferTarget target, GLsizei size, const void *data, BufferUsage usage) {
    Call::slow(glBufferData)(static_cast<GLenum>(target), size, data, static_cast<GLenum>(usage));
}

void genBuffers(GLsizei n, GLuint *id_array) {
    glGenBuffers(n, id_array);
}

void deleteBuffers(GLsizei n, GLuint *id_array) {
    glDeleteBuffers(n, id_array);
}

} // namespace Folk::gl
