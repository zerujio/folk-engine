#ifndef FOLK_RENDER__MATERIAL_DATA_HPP
#define FOLK_RENDER__MATERIAL_DATA_HPP

#include "folk/render/material.hpp"

namespace Folk
{

struct MaterialData final : public Material {
    MaterialData(std::shared_ptr<Shader> shader) : Material(shader) {}
};

} // namespace Folk


#endif // FOLK_RENDER__MATERIAL_DATA_HPP