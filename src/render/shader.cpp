#include "folk/render/shader.hpp"
#include "renderer.hpp"
#include "default_shader.hpp"

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

void Shader::linkProgram(const gl::ShaderHandle vert, const gl::ShaderHandle frag) const {

    for (const auto& p : builtin_attribute_indices) {
        m_shader_program.bindAttribLocation(static_cast<GLuint>(p.second), p.first);
    }

    for (const auto& p : Folk::user_attribute_indices) {
        m_shader_program.bindAttribLocation(p.second, p.first);
    }

    m_shader_program.attach(vert);
    m_shader_program.attach(frag);

    m_shader_program.link();

    m_shader_program.detach(vert);
    m_shader_program.detach(frag);
}

void Shader::compileShadersAndLinkProgram(const char *vert_source, const char *frag_source) const {
    gl::ShaderManager vert {gl::ShaderType::Vertex};
    vert.setSource(vert_source);
    vert.compile();

    gl::ShaderManager frag {gl::ShaderType::Fragment};
    frag.setSource(frag_source);
    frag.compile();

    linkProgram(vert, frag);
}

Shader::Shader(const std::string &vert, const std::string &frag) {
    compileShadersAndLinkProgram(vert.c_str(), frag.c_str());
}

Shader::Shader(const char *vert, const char *frag) {
    compileShadersAndLinkProgram(vert, frag);
}

} // namespace Folk
