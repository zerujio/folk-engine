#include "folk/render/material.hpp"

#include "folk/error.hpp"
#include "folk/render/shader.hpp"

namespace Folk
{

Material::Material(std::shared_ptr<Shader> shader_) : m_shader(std::move(shader_))
{
    addUniforms();
}

std::shared_ptr<Material> Material::create() {
    return std::make_shared<Material>(std::move(Shader::createDefault<PositionVertex>()));
}

std::shared_ptr<Material> Material::create(std::shared_ptr<Shader> shader_) {
    return std::make_shared<Material>(std::move(shader_));
}

void Material::setShader(std::shared_ptr<Shader> shader_)
{
    std::unique_lock lk(mtx);

    m_shader = std::move(shader_);

    m_uniforms.clear();

    addUniforms();
}

std::shared_ptr<Shader> Material::getShader() const {
    //std::unique_lock lk(mtx);

    return m_shader;
}

int Material::uniformIndex(const char *name) const {
    const auto& uniform_decls = m_shader->uniforms();
    for (int i = 0; i < uniform_decls.size(); ++i) {
        if (uniform_decls[i].name == name)
            return i;
    }
    return -1;
}

int Material::uniformIndex(const std::string &name) const {
    return uniformIndex(name.c_str());
}


void Material::addUniforms() {
    for (const auto& uniform : m_shader->uniforms()) {
        m_uniforms.emplace_back(parseUniform(uniform));
    }
}

template<UniformType UT>
std::unique_ptr<IUniform> makeUniform(uint location, std::size_t count) {

    if (count > 1)
        return std::make_unique<Uniform<UTypeRep<UT>[]>>(location, count);

    return std::make_unique<Uniform<UTypeRep<UT>>>(location);
}

template<UniformType UT>
std::unique_ptr<IUniform> makeTexUniform(uint tex_unit, std::size_t count) {

    if (count > 1)
        throw Error("Sampler arrays are not supported.");

    return std::make_unique<Uniform<UTypeRep<UT>>>(tex_unit);
}

std::unique_ptr<IUniform> Material::parseUniform(const Shader::UniformInfo &uniform_decl) {

#define CASE(ENUM) \
case UniformType::ENUM: return makeUniform<UniformType::ENUM>(uniform_decl.location_or_tex_unit, uniform_decl.count);

#define VECTORS(PREFIX) \
CASE(PREFIX ## Vec ## 2)\
CASE(PREFIX ## Vec ## 3)\
CASE(PREFIX ## Vec ## 4)

#define MATRIX(PREFIX, DIM) CASE(PREFIX ## Mat ## DIM)

#define MATRICES(PREFIX) \
MATRIX(PREFIX, 2)        \
MATRIX(PREFIX, 3)        \
MATRIX(PREFIX, 4)        \
MATRIX(PREFIX, 2x3)      \
MATRIX(PREFIX, 2x4)      \
MATRIX(PREFIX, 3x2)      \
MATRIX(PREFIX, 3x4)      \
MATRIX(PREFIX, 4x2)      \
MATRIX(PREFIX, 4x3)

#define SAMPLER(ENUM) \
case UniformType::ENUM: \
    return makeTexUniform<UniformType::ENUM>(uniform_decl.location_or_tex_unit, uniform_decl.count);

    switch (uniform_decl.type) {
        CASE(Int)
        VECTORS(i)

        CASE(UInt)
        VECTORS(u)

        CASE(Float)
        VECTORS(f)
        MATRICES(f)

        CASE(Double)
        VECTORS(d)
        MATRICES(d)

        CASE(Bool)
        VECTORS(b)

        SAMPLER(sampler1D)
        SAMPLER(sampler1DArray)
        SAMPLER(sampler2D)
        SAMPLER(sampler2DArray)
        SAMPLER(sampler2DRect)
        SAMPLER(sampler2DMS)
        SAMPLER(sampler2DMSArray)
        SAMPLER(sampler3D)
        SAMPLER(samplerCube)
        SAMPLER(samplerBuffer)

        default:
            throw Error("Unsupported uniform type: " + std::string(uniformTypeName(uniform_decl.type)));
    }
}

unsigned int Material::uniformCount() const {
    return m_uniforms.size();
}

} // namespace folk
