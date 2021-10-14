#ifndef FOLK_RENDER__MESH_DATA_HPP
#define FOLK_RENDER__MESH_DATA_HPP

#include "folk/render/mesh.hpp"
#include "common.hpp"

namespace Folk
{

struct MeshData {
    GLuint vbo;
    GLuint ebo;
    GLsizei count;

    MeshData(GLuint vbo_, GLuint ebo_, GLsizei count_) 
        : vbo(vbo_), ebo(ebo_), count(count_)
    {}
};

} // namespace Folk


#endif // FOLK_RENDER__MESH_DATA_HPP