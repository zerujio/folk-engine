//
// Created by sergio on 06-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_VERTEX_ARRAY_HPP
#define INCLUDE_FOLK_RENDER__GL_VERTEX_ARRAY_HPP

#include "gl_object.hpp"

namespace Folk::gl {

GLboolean isVertexArray(GLuint id);

class VertexArray : public BaseHandle<isVertexArray> {

public:
    /// use this VAO
    void bind() const;

    /// Unbind the currently bound VAO.
    static void unbind();
};

void genVertexArrays(GLsizei n, GLuint* ids);
void deleteVertexArrays(GLsizei n, GLuint* ids);

using VertexArrayManager = ObjectManager<VertexArray, genVertexArrays, deleteVertexArrays>;

}

#endif //INCLUDE_FOLK_RENDER__GL_VERTEX_ARRAY_HPP
