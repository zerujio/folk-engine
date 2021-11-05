#ifndef FOLK_RENDER__MESH_DATA_HPP
#define FOLK_RENDER__MESH_DATA_HPP

#include "folk/render/mesh.hpp"

namespace Folk
{

struct MeshData final : public Mesh {
    const bgfx::VertexBufferHandle vb_handle;
    const bgfx::IndexBufferHandle ib_handle;

    MeshData(bgfx::VertexBufferHandle vb, bgfx::IndexBufferHandle ib)
        : vb_handle(vb), ib_handle(ib)
    {}

    ~MeshData() {
        bgfx::destroy(vb_handle);
        bgfx::destroy(ib_handle);
    }
};

} // namespace Folk


#endif // FOLK_RENDER__MESH_DATA_HPP