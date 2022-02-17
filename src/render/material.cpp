#include "folk/render/material.hpp"

#include "folk/error.hpp"
#include "folk/render/shader.hpp"

#include "../core/engine.hpp"

#include "uniform_type_info.hpp"

namespace Folk
{

Material::Material(std::shared_ptr<Shader> shader_) : m_shader(std::move(shader_))
{
    addUniforms();
}


std::shared_ptr<Material> Material::create() {
    return create(Shader::createDefault());
}

std::shared_ptr<Material> Material::create(std::shared_ptr<Shader> shader_) {
    return std::make_shared<Material>(std::move(shader_));
}

void Material::setShader(std::shared_ptr<Shader> shader_)
{
    std::unique_lock lk(mtx);

    m_shader = std::move(shader_);

    m_uniform_info.clear();
    m_uniform_data.clear();

    addUniforms();
}

std::shared_ptr<Shader> Material::getShader() const {
    //std::unique_lock lk(mtx);

    return m_shader;
}

Material::ConstUniform Material::uniform(unsigned int index) const {
    return {*this, index};
}

Material::Uniform Material::uniform(unsigned int index) {
    return {*this, index};
}

// adds uniforms from m_shader to m_uniform_info and m_uniform_data;
void Material::addUniforms() {
    for (const auto& uniform : m_shader->uniforms()) {

        // allocate storage space
        unsigned int required_space = uniform.type_info.size() / sizeof(StorageUnit)
                                    + (uniform.type_info.size() % sizeof(StorageUnit) != 0);
        unsigned int data_index = m_uniform_data.size();
        m_uniform_data.insert(m_uniform_data.end(), required_space, 0);

        // add to uniform vector
        m_uniform_info.insert(m_uniform_info.end(), {data_index, false});
    }
}

Material::ConstUniform Material::uniform(const std::string &name) const {
    return uniform(name.c_str());
}

Material::ConstUniform Material::uniform(const char *name) const {

    auto index = uniformIndex(name);

    if (index < 0) {
        std::string err_msg = "No uniform named ";
        err_msg += name;
        throw Error(err_msg);
    } else {
        return uniform(index);
    }
}

Material::Uniform Material::uniform(const std::string &name) {
    return uniform(name.c_str());
}

Material::Uniform Material::uniform(const char *name) {
    auto index = uniformIndex(name);

    if (index < 0) {
        std::string err_msg = "No uniform named ";
        err_msg += name;
        throw Error(err_msg);
    } else {
        return uniform(index);
    }
}


int Material::uniformIndex(const char *name) const {
    for (int i = 0; i < m_uniform_info.size(); ++i) {
        if (m_shader->uniforms()[i].name == name)
            return i;
    }
    return -1;
}

int Material::uniformIndex(const std::string &name) const {
    return uniformIndex(name.c_str());
}

} // namespace folk
