#include "folk/render/mesh.hpp"

#include "../core/engine.hpp"

#include "renderer.hpp"

namespace Folk
{

std::shared_ptr<Mesh> Mesh::create(ImmediateGeometry const& geom) {
    return std::make_shared<Mesh>();
}

} // namespace folk
