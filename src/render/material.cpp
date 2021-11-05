#include "folk/core/error.hpp"
#include "folk/render/material.hpp"

#include "../core/engine_singleton.hpp"

#include "shader_data.hpp"
#include "material_data.hpp"

namespace Folk
{

std::shared_ptr<Material> Material::create() {
    return create(Shader::createDefault());
}

std::shared_ptr<Material> Material::create(std::shared_ptr<Shader> shader) {
    auto sptr = std::make_shared<MaterialData>(shader);
    return std::shared_ptr<Material>(sptr, sptr.get());
}

Material::Material(std::shared_ptr<Shader> shader) : shader(shader) {}

void Material::setShader(std::shared_ptr<Shader> shader_)
{
    std::unique_lock lk(mtx);

    shader = shader_;
}

std::shared_ptr<Shader> Material::getShader() {
    std::unique_lock lk(mtx);

    return shader;
}
    
} // namespace folk
