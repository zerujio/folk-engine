#include "folk/render/mesh.hpp"
#include "../core/engine_singleton.hpp"

namespace folk
{

// copy opengl buffer
static void copyBuffer(GLuint from, GLuint to) {
    glBindBuffer(GL_COPY_READ_BUFFER, from);
    glBindBuffer(GL_COPY_WRITE_BUFFER, to);
    GLint size;
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
    /* 
    ENGINE.out 
        << "copied " << size << "bytes from buffer" << from 
        << "to buffer " << to << "\n"; 
    */
}

template <class T>
static void writeBuffer(GLenum target, GLuint buffer, GLenum draw_mode, 
                        std::vector<T> const&data)
{
    int size = data.size() * sizeof(T);

    glBindBuffer(target, buffer);
    glBufferData(target, size, data.data(), draw_mode);
    /* 
    ENGINE.out << "Wrote " << size << " bytes to buffer " << buffer << ": {";
    for (auto x : data)
        ENGINE.out << x << " ";
    ENGINE.out << "}\n";
    */
}

Mesh::Ref Mesh::createEmpty() {
    return Mesh::Ref(new Mesh(VertexArray(), IndexArray(), 6));
}

Reference<Mesh> Mesh::create(ImmediateGeometry const& geom) {
    return Reference<Mesh>(new Mesh(geom.vertices, geom.indices, geom.stride));
}

Mesh::Mesh(VertexArray const& vertices, IndexArray const& indices, 
        GLuint stride_)
    : stride(stride_), index_count(indices.size())
{
    // create vbo, ebo
    glGenBuffers(2, buffers);
    // ENGINE.out << "Created two buffers {vbo=" << vbo << ", ebo=" << ebo << "}\n";
    
    writeBuffer(GL_ARRAY_BUFFER, vbo, GL_STATIC_DRAW, vertices);
    writeBuffer(GL_ARRAY_BUFFER, ebo, GL_STATIC_DRAW, indices);
}

Mesh::~Mesh()
{
    glDeleteBuffers(2, buffers);
    // ENGINE.out << "Deleted buffers: " << vbo << ", " << ebo << "\n";
}

Mesh::Mesh(Mesh const& other) 
    : stride(other.stride), index_count(other.index_count)
{
    glGenBuffers(2, buffers);
    copyBuffer(other.vbo, vbo);
    copyBuffer(other.ebo, ebo);
}

Mesh& Mesh::operator=(Mesh const& other) {
    stride = other.stride;
    index_count = other.index_count;
    copyBuffer(other.vbo, vbo);
    copyBuffer(other.ebo, ebo);

    return *this;
}

} // namespace folk
