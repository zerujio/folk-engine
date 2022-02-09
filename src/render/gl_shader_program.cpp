#include "folk/render/gl_shader_program.hpp"

namespace Folk::gl {

GLboolean _isProgram(GLuint id) {
    return glIsProgram(id);
}

void ShaderProgramHandle::link() const {
    Call::fast(glLinkProgram)(id());
}

void ShaderProgramHandle::attach(ShaderHandle shader) const {
    Call::fast(glAttachShader)(id(), shader.id());
}

void ShaderProgramHandle::detach(ShaderHandle shader) const {
    Call::fast(glDetachShader)(id(), shader.id());
}

void ShaderProgramHandle::use() const {
    Call::fast(glUseProgram)(id());
}

GLuint _createProgram() {
    return glCreateProgram();
}

void _deleteProgram(GLuint id) {
    return glDeleteProgram(id);
}

} // namespace Folk::gl
