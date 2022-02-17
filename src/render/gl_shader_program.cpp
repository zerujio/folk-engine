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

GLint ShaderProgram::getInterface(Interface interface, InterfaceParam param) const {
    GLint value;
    Call::fast(glGetProgramInterfaceiv)(id(), static_cast<GLenum>(interface), static_cast<GLenum>(param), &value);
    return value;
}

void ShaderProgram::getResource(ShaderProgram::Interface interface, GLuint resource_index, GLsizei property_count,
                                const ShaderProgram::ResourceProp *properties, GLsizei value_buffer_size,
                                GLsizei *value_lengths, GLint *value_buffer) const
{
    Call::slow(glGetProgramResourceiv)(id(), static_cast<GLenum>(interface), resource_index,
            property_count, reinterpret_cast<const GLenum*>(properties),
            value_buffer_size, value_lengths, value_buffer);
}

void ShaderProgram::getResource(ShaderProgram::Interface interface, GLuint resource_index,
                                const std::vector<ResourceProp> &properties, std::vector<GLsizei> &value_lengths,
                                std::vector<GLint> &values) const
{
    if (value_lengths.size() != properties.size())
        value_lengths.resize(properties.size());

    getResource(interface, resource_index,
                properties.size(), properties.data(),
                values.size(), value_lengths.data(), values.data());
}

void ShaderProgram::getResource(ShaderProgram::Interface interface, GLuint resource_index,
                                const std::vector<ResourceProp> &properties, std::vector<GLint> &values) const {
    getResource(interface, resource_index, properties.size(), properties.data(), values.size(), nullptr, values.data());
}

std::string ShaderProgram::getResourceName(ShaderProgram::Interface interface, GLuint resource_index) const {
    GLint char_array_length;
    const auto name_property = ResourceProp::NameLength;
    getResource(interface, resource_index, 1, &name_property, 1, nullptr, &char_array_length);
    std::string string (char_array_length, char());
    Call::fast(glGetProgramResourceName)(id(), static_cast<GLenum>(interface), resource_index, char_array_length,
                                         nullptr, string.data());
}


GLuint _createProgram() {
    return glCreateProgram();
}

void _deleteProgram(GLuint id) {
    return glDeleteProgram(id);
}

} // namespace Folk::gl
