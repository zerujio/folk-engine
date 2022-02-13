#include "folk/render/mesh.hpp"

#include "../core/engine.hpp"

#include "renderer.hpp"

namespace Folk
{

std::shared_ptr<Mesh> Mesh::createCube() {

    std::array<PositionVertex, 8> vertices {
            PositionVertex
            {-1.0f,  1.0f,  1.0f},
            { 1.0f,  1.0f,  1.0f},
            {-1.0f, -1.0f,  1.0f},
            { 1.0f, -1.0f,  1.0f},
            {-1.0f,  1.0f, -1.0f},
            { 1.0f,  1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},
            { 1.0f, -1.0f, -1.0f}
    };

    std::array<GLushort, 36> indices {
        0, 1, 2,
        1, 3, 2,
        4, 6, 5,
        5, 6, 7,
        0, 2, 4,
        4, 2, 6,
        1, 5, 3,
        5, 7, 3,
        0, 4, 1,
        4, 5, 1,
        2, 3, 6,
        6, 3, 7,
    };

    return std::make_shared<Mesh>( vertices, indices );
}

void Mesh::configureVertexAttribute(GLuint index, const VertexAttribute &attribute, GLsizei stride, GLuint offset) {
    gl::call::fast(glVertexAttribPointer)(
            index,
            static_cast<GLint>(attribute.count),
            static_cast<GLenum>(attribute.type.gl_enum),
            attribute.normalize,
            stride,
            reinterpret_cast<void*>(offset));
    gl::call::fast(glEnableVertexAttribArray)(index);
}

} // namespace folk
