#include "folk/core/error.hpp"
#include "folk/render/material.hpp"

#include "folk/render/shader.hpp"

#include "../core/engine_singleton.hpp"

namespace Folk
{

std::shared_ptr<Material> Material::create() {
    return create(Shader::createDefault());
}

std::shared_ptr<Material> Material::create(std::shared_ptr<Shader> shader) {
    return std::make_shared<Material>(shader);
}

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
