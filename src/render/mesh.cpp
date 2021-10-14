#include "folk/render/mesh.hpp"
#include "../core/engine_singleton.hpp"
#include "common.hpp"
#include "module.hpp"

namespace Folk
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
    return Ref(new Mesh(VertexArray(), IndexArray()));
}

Mesh::Ref Mesh::create(ImmediateGeometry const& geom) {
    return Ref(new Mesh(geom.vertices, geom.indices));
}

Mesh::Mesh(VertexArray const& vertices, IndexArray const& indices)
{
    GLuint buffers[2];
    GLuint &vbo = buffers[0], &ebo = buffers[1];

    // create vbo, ebo
    glGenBuffers(2, buffers);
    // ENGINE.out << "Created two buffers {vbo=" << vbo << ", ebo=" << ebo << "}\n";
    
    writeBuffer(GL_ARRAY_BUFFER, vbo, GL_STATIC_DRAW, vertices);
    writeBuffer(GL_ARRAY_BUFFER, ebo, GL_STATIC_DRAW, indices);

    RENDER.meshes.emplace(id, MeshData(vbo, ebo, indices.size()));
}

Mesh::~Mesh()
{ 
    MeshData& mesh = RENDER.meshes.at(id);
    GLuint buffers[2] {mesh.vbo, mesh.vbo};
    glDeleteBuffers(2, buffers);
    // ENGINE.out << "Deleted buffers: " << vbo << ", " << ebo << "\n";
    RENDER.meshes.erase(id);
}

Mesh::Mesh(Mesh const& other) 
{
    GLuint buffers[2];
    GLuint &vbo {buffers[0]}, &ebo {buffers[1]};
    glGenBuffers(2, buffers);

    MeshData const& other_data = RENDER.meshes.at(other.id);

    copyBuffer(other_data.vbo, vbo);
    copyBuffer(other_data.ebo, ebo);

    RENDER.meshes.emplace(id, MeshData(vbo, ebo, other_data.count));
}

Mesh& Mesh::operator=(Mesh const& other) {
    MeshData& data = RENDER.meshes.at(id);
    MeshData const& other_data = RENDER.meshes.at(other.id);

    copyBuffer(other_data.vbo, data.vbo);
    copyBuffer(other_data.ebo, data.ebo);

    data.count = other_data.count;

    return *this;
}

Mesh::Mesh(Mesh&& other)
{
    MeshData& other_data = RENDER.meshes.at(other.id);
    RENDER.meshes.emplace(id, other_data);
    
    GLuint bufs[2];
    glGenBuffers(2, bufs);

    other_data.ebo = bufs[0];
    other_data.vbo = bufs[1];
    other_data.count = 0;
}

Mesh& Mesh::operator=(Mesh&& other)
{
    MeshData& data = RENDER.meshes.at(id);
    MeshData& other_data = RENDER.meshes.at(other.id);

    data = other_data;
    
    GLuint bufs[2];
    glGenBuffers(2, bufs);

    other_data.ebo = bufs[0];
    other_data.vbo = bufs[1];
    other_data.count = 0;

    return *this;
}

} // namespace folk
