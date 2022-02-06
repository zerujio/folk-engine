//
// Created by sergio on 06-02-22.
//

#include "folk/render/gl_vertex_array.hpp"

namespace Folk {

GLboolean gl::isVertexArray(const GLuint id) {
    return glIsVertexArray(id);
}

void gl::genVertexArrays(const GLsizei n, GLuint *ids) {
    glGenVertexArrays(n, ids);
}

void gl::deleteVertexArrays(const GLsizei n, GLuint *ids) {
    glDeleteVertexArrays(n, ids);
}

void gl::VertexArrayHandle::bind() const {
    glBindVertexArray(id());
}

}
