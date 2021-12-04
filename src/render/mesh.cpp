#include "folk/render/mesh.hpp"

#include "../core/engine_singleton.hpp"

#include "common.hpp"
#include "renderer.hpp"

namespace Folk
{

Mesh::Mesh(const bgfx::VertexBufferHandle vb_, 
           const bgfx::IndexBufferHandle ib_)
    : vb(vb_), ib(ib_)
{}

Mesh::~Mesh() {
    bgfx::destroy(vb);
    bgfx::destroy(ib);
}

static bgfx::VertexLayout posColorVertLayout() {
    static bgfx::VertexLayout layout;
    static bool initialized = false;

    if (!initialized) {
        layout.begin()
           .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
           .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
           .end();

        initialized = true;
    }

    return layout;
}

static const bgfx::VertexBufferHandle createVB(ImmediateGeometry const& geo) {
    auto memptr = bgfx::copy(geo.vertices.data(), 
                             geo.vertices.size() * sizeof(ImmediateGeometry::Vertex));
    auto handle = bgfx::createVertexBuffer(memptr, posColorVertLayout());

    if (!bgfx::isValid(handle))
        throw FOLK_RUNTIME_ERROR("Vertex buffer creation failed!");

    return handle;
}

static const bgfx::IndexBufferHandle createIB(ImmediateGeometry const& geo) {
    auto mem = bgfx::copy(geo.indices.data(),
                          geo.indices.size() * sizeof(ImmediateGeometry::Index));
    auto handle = bgfx::createIndexBuffer(mem);

    if (!bgfx::isValid(handle))
        throw FOLK_RUNTIME_ERROR("Index buffer creation failed");

    return handle;
}

static std::shared_ptr<Mesh> createMesh(const bgfx::VertexBufferHandle vb,
                                        const bgfx::IndexBufferHandle ib)
{
    return std::make_shared<Mesh>(vb, ib);
}

std::shared_ptr<Mesh> Mesh::create(ImmediateGeometry const& geom) {
    return createMesh(createVB(geom), createIB(geom));
}

} // namespace folk
