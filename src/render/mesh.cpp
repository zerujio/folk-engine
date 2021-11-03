#include "folk/render/mesh.hpp"
#include "../core/engine_singleton.hpp"
#include "common.hpp"
#include "renderer.hpp"

namespace Folk
{

Mesh::Ref Mesh::createEmpty() {
    return Ref(new Mesh({}, {}));
}

Mesh::Ref Mesh::create(ImmediateGeometry const& geom) {
    return Ref(new Mesh(geom.vertices, geom.indices));
}

Mesh::Mesh(ImmediateGeometry::VertexArray const& vertices, 
           ImmediateGeometry::IndexArray const& indices)
{
    bgfx::VertexLayout layout;
    layout.begin(bgfx::RendererType::OpenGL)
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8)
            .end();

    const bgfx::Memory* vb_mem = bgfx::copy(
        vertices.data(), 
        sizeof(ImmediateGeometry::Vertex) * vertices.size()
    );
    bgfx::VertexBufferHandle vb_handle = bgfx::createVertexBuffer(vb_mem, layout);

    const bgfx::Memory* ib_mem = bgfx::copy(
        indices.data(),
        sizeof(ImmediateGeometry::Index) * indices.size()
    );

    bgfx::IndexBufferHandle ib_handle = bgfx::createIndexBuffer(ib_mem);

    RENDER.meshes[id] = {vb_handle, ib_handle};
}

Mesh::~Mesh()
{ 
    auto& data = RENDER.meshes[id];

    bgfx::destroy(data.vb_handle);
    bgfx::destroy(data.ib_handle);

    RENDER.meshes.erase(id);
}

} // namespace folk
