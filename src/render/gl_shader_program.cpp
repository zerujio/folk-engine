#include "folk/render/gl_shader_program.hpp"

namespace Folk::gl {

GLboolean _isProgram(GLuint id) {
    return glIsProgram(id);
}

void ShaderProgramHandle::link() const {
    Call::fast(glLinkProgram)(id());
    GLint success;
    Call::fast(glGetProgramiv)(id(), GL_LINK_STATUS, &success);
    if (!success) {
        std::array<char, 1024> buf {};
        Call::fast(glGetProgramInfoLog)(id(), buf.size(), nullptr, buf.data());
        Log::error() << "[GL ERROR] Shader linking failed: " << buf.data() << "\n";
    }
}

void ShaderProgramHandle::attach(ShaderHandle shader) const {
    Call::fast(glAttachShader)(id(), shader.id());
}

void ShaderProgramHandle::detach(ShaderHandle shader) const {
    Call::fast(glDetachShader)(id(), shader.id());
}

void ShaderProgramHandle::bind() const {
    Call::fast(glUseProgram)(id());
}

void ShaderProgramHandle::unbind() {
    Call::fast(glUseProgram)(0u);
}

GLuint _createProgram() {
    return glCreateProgram();
}

void _deleteProgram(GLuint id) {
    return glDeleteProgram(id);
}

} // namespace Folk::gl
