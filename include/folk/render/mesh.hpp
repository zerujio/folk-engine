#ifndef FOLK_RENDER__MESH_HPP
#define FOLK_RENDER__MESH_HPP


#include "folk/core/resource.hpp"
#include "folk/render/immediate_geometry.hpp"
#include "folk/render/common.hpp"

namespace Folk
{

class Mesh : public Resource {
public:
    using Ref = Reference<Mesh>;
    static Ref createEmpty();
    static Ref create(ImmediateGeometry const&);

    ~Mesh();

private:
    GLuint buffers [2];
    GLuint &vbo {buffers[0]};
    GLuint &ebo {buffers[1]};
    GLuint stride;
    GLuint index_count;

    Mesh(VertexArray const&, IndexArray const&, GLuint);
    Mesh(Mesh const&);
    Mesh& operator=(Mesh const&);


    friend class RenderModule;
    friend class Visual;
};
    
} // namespace folk

#endif // FOLK_RENDER__MESH_HPP