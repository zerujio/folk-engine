#include "folk/render/gl_buffer.hpp"

namespace Folk::gl {

GLboolean isBuffer(GLuint id) {
    return glIsBuffer(id);
}

void BufferHandle::bind(BufferTarget target) const {
    Call::fast(glBindBuffer)(static_cast<GLenum>(target), id());
}

void BufferHandle::unbind(BufferTarget target) {
    Call::fast(glBindBuffer)(static_cast<GLenum>(target), 0);
}

void genBuffers(GLsizei n, GLuint *id_array) {
    glGenBuffers(n, id_array);
}

void deleteBuffers(GLsizei n, GLuint *id_array) {
    glDeleteBuffers(n, id_array);
}

} // namespace Folk::gl
