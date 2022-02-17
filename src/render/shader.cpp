#include "folk/render/shader.hpp"
#include "renderer.hpp"
#include "default_shader.hpp"
#include "uniform_type_info.hpp"

#include <fstream>
#include <sstream>

namespace Folk
{

std::vector<std::pair<const char*, GLuint>> user_attribute_indices {};

Shader::Ref Shader::createDefault() {
    return std::make_shared<Shader>(default_vert_source_code, default_frag_source_code);
}

std::string readShaderSource(const char* filename) {
    std::ifstream file {filename};
    std::stringstream buffer {};
    buffer << file.rdbuf();
    return buffer.str();
}

Shader::Ref Shader::createFromFiles(const char* vert, const char* frag) {
    return std::make_shared<Shader>(readShaderSource(vert), readShaderSource(frag));
}

Shader::Shader(const std::string &vert, const std::string &frag) : Shader(vert.c_str(), frag.c_str()) {}

Shader::Shader(const char *vert_src, const char *frag_src) {

    compileAndLink(vert_src, frag_src);
    parseUniforms();
}

void Shader::compileAndLink(const char* vert_src, const char* frag_src) {
    // compile shaders
    gl::ShaderManager vert {gl::ShaderType::Vertex};
    vert.setSource(vert_src);
    vert.compile();

    gl::ShaderManager frag {gl::ShaderType::Fragment};
    frag.setSource(frag_src);
    frag.compile();

    // bind attribute indices
    for (const auto& p : builtin_attribute_indices) {
        m_shader_program.bindAttribLocation(static_cast<GLuint>(p.second), p.first);
    }

    for (const auto& p : Folk::user_attribute_indices) {
        m_shader_program.bindAttribLocation(p.second, p.first);
    }

    // link program
    m_shader_program.attach(vert);
    m_shader_program.attach(frag);

    m_shader_program.link();

    m_shader_program.detach(vert);
    m_shader_program.detach(frag);
}

void Shader::parseUniforms() {
    // get uniform count.
    GLint n_active_uniforms = m_shader_program.getInterface(gl::ShaderProgram::Interface::Uniform,
                                                            gl::ShaderProgram::InterfaceParam::ActiveResources);

    for (uint i = 0; i < n_active_uniforms; ++i) {

        auto name = m_shader_program.getResourceName(gl::ShaderProgram::Interface::Uniform, i);

        std::array uniform_info {0, 0, 0};
        m_shader_program.getResource(gl::ShaderProgram::Interface::Uniform, i,
                                     std::array{gl::ShaderProgram::ResourceProp::Location,
                                                gl::ShaderProgram::ResourceProp::Type,
                                                gl::ShaderProgram::ResourceProp::ArraySize},
                                     uniform_info);

        if (uniform_info[0] < 0)
            continue; // skip block uniforms

        // parse uniform info.
        auto location = static_cast<GLuint>(uniform_info[0]);
        auto type = static_cast<UniformType>(uniform_info[1]);
        auto count = static_cast<GLuint>(uniform_info[2]);
        if (!count) count = 1; // count will be zero if uniform is not an array.

        // check builtin name list
        auto name_iter = builtin_uniform_names.begin();
        while (name_iter != builtin_uniform_names.end()) {
            if (name_iter->first == name)
                break;
            ++name_iter;
        }

        // if builtin...
        if (name_iter != builtin_uniform_names.end()) {
            parseBuiltInUniform(name_iter->first, name_iter->second, type, count, location);
        } else {
            // add to user defined uniforms
            m_uniforms.emplace_back(name, type, count, location);
        }
    }
}

void Shader::parseBuiltInUniform(const char* name, Shader::BuiltInUniform u_id, UniformType type, GLuint count, GLuint location) {
    // check type
    auto builtin_type = getBuiltInUniformType(u_id);
    if (type != builtin_type) {
        std::stringstream err_msg {};
        err_msg << "Shader: built-in uniform " << name << " defined with incorrect type.";

        throw Error(err_msg.str());
    }

    // check size.
    auto expected_count = 1;
    if (count != expected_count) {
        std::stringstream err_msg {};
        err_msg << "Shader: built-in uniform " << name << " defined with incorrect size. ";
        throw Error(err_msg.str());
    }

    builtInUniformLoc(u_id) = location;
}


// Uniform

int &Shader::builtInUniformLoc(Shader::BuiltInUniform u) {
    return m_builtin_uniform_locations[static_cast<unsigned int>(u)];
}

const int &Shader::builtInUniformLoc(Shader::BuiltInUniform u) const {
    return m_builtin_uniform_locations[static_cast<unsigned int>(u)];
}

Shader::Uniform::Uniform(std::string name_, UniformType type_, unsigned int count_, unsigned int location_)
: name(std::move(name_)),
    type(type_),
    count(count_),
    location(location_),
    type_info(UniformTypeInfo::get(type))
{}

} // namespace Folk
