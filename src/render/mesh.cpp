#include "folk/render/mesh.hpp"

#include "../core/engine_singleton.hpp"

#include "common.hpp"
#include "renderer.hpp"

namespace Folk
{

std::shared_ptr<Mesh> Mesh::create(ImmediateGeometry const& geom) {
    return std::make_shared<Mesh>();
}

} // namespace folk
