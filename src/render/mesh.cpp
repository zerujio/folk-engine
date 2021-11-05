#include "folk/render/mesh.hpp"

#include "../core/engine_singleton.hpp"

#include "mesh_data.hpp"
#include "common.hpp"
#include "renderer.hpp"

namespace Folk
{

static bgfx::VertexLayout posColorVertLayout() {
    static bgfx::VertexLayout layout;
    static bool initialized = false;

    if (!initialized) {
        layout.begin()
           .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
           .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8)
           .end();
    }

    return layout;
}

static bgfx::VertexBufferHandle emptyVB() {
    auto mem = bgfx::copy(nullptr, 0);
    auto handle = bgfx::createVertexBuffer(mem, posColorVertLayout());

    if (!bgfx::isValid(handle))
        throw CriticalEngineError("empty VertexBuffer creation failed!");

    bgfx::setName(handle, "Emtpy VB");

    return handle;
}

static bgfx::IndexBufferHandle emptyIB() {
    auto mem = bgfx::copy(nullptr, 0);
    auto handle = bgfx::createIndexBuffer(mem);

    if (!bgfx::isValid(handle))
        throw CriticalEngineError("empty IndexBuffer creation failed!");

    bgfx::setName(handle, "Empty IB");

    return handle;
}

static const bgfx::VertexBufferHandle createVB(ImmediateGeometry const& geo) {
    auto memptr = bgfx::copy(geo.vertices.data(), 
                                   geo.vertices.size() * sizeof(ImmediateGeometry::Vertex));
    auto handle = bgfx::createVertexBuffer(memptr, posColorVertLayout());

    return handle;
}

static const bgfx::IndexBufferHandle createIB(ImmediateGeometry const& geo) {
    auto mem = bgfx::copy(geo.indices.data(),
                          geo.indices.size() * sizeof(ImmediateGeometry::Index));
    auto handle = bgfx::createIndexBuffer(mem);

    return handle;
}

static std::shared_ptr<Mesh> createMesh(bgfx::VertexBufferHandle vb,
                                    bgfx::IndexBufferHandle ib)
{
    std::shared_ptr<MeshData> ptr = std::make_shared<MeshData>(vb, ib);
    return std::shared_ptr<Mesh>(ptr, ptr.get());
}

std::shared_ptr<Mesh> Mesh::create(ImmediateGeometry const& geom) {
    return createMesh(createVB(geom), createIB(geom));
}

std::shared_ptr<Mesh> Mesh::create() {
    return createMesh(emptyVB(), emptyIB());
}

} // namespace folk
