#include "folk/render/material.hpp"
#include "folk/core/error.hpp"
#include "../core/engine_singleton.hpp"

namespace Folk
{

Material::Ref Material::createDefaultMaterial() {
    return Ref(new Material(Shader::createDefaultShader()));
}

Material::Ref Material::create(Shader::Ref shader)
{
    return Ref(new Material(shader));
}

Material::Material(Shader::Ref shader) : shader(shader) {}

Material::~Material() {}
    
} // namespace folk
