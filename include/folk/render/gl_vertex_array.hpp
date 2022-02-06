//
// Created by sergio on 06-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_VERTEX_ARRAY_HPP
#define INCLUDE_FOLK_RENDER__GL_VERTEX_ARRAY_HPP

#include "gl_handle.hpp"
#include "folk/utils/object_manager.hpp"

namespace Folk::gl {

GLboolean isVertexArray(GLuint id);

class VertexArrayHandle : public BaseHandle<isVertexArray> {

public:
    /// bind this VAO
    void bind() const;

    /// Unbind the currently bound VAO.
    static void unbind();
};

void genVertexArrays(GLsizei n, GLuint* ids);
void deleteVertexArrays(GLsizei n, GLuint* ids);

using VertexArrayManager = ObjectManager<VertexArrayHandle, genVertexArrays, deleteVertexArrays>;

}

#endif //INCLUDE_FOLK_RENDER__GL_VERTEX_ARRAY_HPP
