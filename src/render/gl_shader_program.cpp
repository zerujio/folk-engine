#include "folk/render/gl_shader_program.hpp"

namespace Folk::gl {

GLboolean _isProgram(GLuint id) {
    return glIsProgram(id);
}

void ShaderProgram::link() const {
    Call::fast(glLinkProgram)(id());
    GLint success;
    Call::fast(glGetProgramiv)(id(), GL_LINK_STATUS, &success);
    if (!success) {
        std::array<char, 1024> buf {};
        Call::fast(glGetProgramInfoLog)(id(), buf.size(), nullptr, buf.data());
        Log::error() << "[GL ERROR] Shader linking failed: " << buf.data() << "\n";
    }
}

void ShaderProgram::attach(ShaderHandle shader) const {
    Call::fast(glAttachShader)(id(), shader.id());
}

void ShaderProgram::detach(ShaderHandle shader) const {
    Call::fast(glDetachShader)(id(), shader.id());
}

void ShaderProgram::bind() const {
    Call::fast(glUseProgram)(id());
}

void ShaderProgram::unbind() {
    Call::fast(glUseProgram)(0u);
}

void ShaderProgram::bindAttribLocation(GLuint index, const char* name) const {
    Call::fast(glBindAttribLocation)(id(), index, name);
}

GLuint _createProgram() {
    return glCreateProgram();
}

void _deleteProgram(GLuint id) {
    return glDeleteProgram(id);
}

} // namespace Folk::gl
