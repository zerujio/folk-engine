#include "folk/render/gl_shader.hpp"

namespace Folk::gl {

void ShaderHandle::compile() const {
    Call::slow(glCompileShader)(id());
}

void ShaderHandle::setSource(const char *source_string) const {
    Call::slow(glShaderSource)(id(), 1, &source_string, nullptr);
}

void ShaderHandle::setSource(const std::string &source_string) const {
    setSource(source_string.c_str());
}

void ShaderHandle::setSource(const std::vector<std::string> &source_strings) const {
    std::vector<const char *> c_strings {source_strings.size()};
    for (int i = 0; i < source_strings.size(); ++i) {
        c_strings[i] = source_strings[i].c_str();
    }
    setSource(c_strings.size(), c_strings.data());
}

void ShaderHandle::setSource(const std::vector<const char *> &source_strings) const {
    setSource(source_strings.size(), source_strings.data());
}

void ShaderHandle::setSource(const std::vector<const char *> &source_strings, const std::vector<GLint>& lengths) const {
    if (source_strings.size() != lengths.size())
        throw Error("string vector and length vector have different sizes");

    setSource(source_strings.size(), source_strings.data(), lengths.data());
}

void ShaderHandle::setSource(int count, const char *const *strings) const {
    Call::fast(glShaderSource)(id(), count, strings, nullptr);
}

void ShaderHandle::setSource(int count, const char *const *strings, const GLint *lengths) const {
    Call::fast(glShaderSource)(id(), count, strings, lengths);
}

GLboolean _isShader(GLuint id) {
    return glIsShader(id);
}

GLuint _createShader(const ShaderType type) {
    return glCreateShader(static_cast<GLenum>(type));
}

void _deleteShader(GLuint id) {
    return glDeleteShader(id);
}

} // namespace Folk::gl
