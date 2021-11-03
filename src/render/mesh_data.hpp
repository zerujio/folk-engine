#ifndef FOLK_RENDER__MESH_DATA_HPP
#define FOLK_RENDER__MESH_DATA_HPP

#include "common.hpp"

namespace Folk
{

struct MeshData {
    bgfx::VertexBufferHandle vb_handle;
    bgfx::IndexBufferHandle ib_handle;
};

} // namespace Folk


#endif // FOLK_RENDER__MESH_DATA_HPP