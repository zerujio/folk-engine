#include "folk/render/gl_texture.hpp"

namespace Folk::gl {

GLboolean isTexture(GLuint id) {
    return glIsTexture(id);
}

void genTextures(GLsizei n, GLuint* ids) {
    return glGenTextures(n, ids);
}

void deleteTextures(GLsizei n, GLuint* ids) {
    return glDeleteTextures(n, ids);
}

void Texture::bind(Texture::Target target) const {
    Call::fast(glBindTexture)(static_cast<GLenum>(target), id());
}

void Texture::unbind(Texture::Target target) {
    Call::fast(glBindTexture)(static_cast<GLenum>(target), 0);
}

void Texture::texImage2D(Target target,
                         GLint level,
                         InternalFormat internal_format,
                         GLsizei width,
                         GLsizei height,
                         Format format,
                         Type type,
                         const void *data) {
    Call::slow(glTexImage2D)(static_cast<GLenum>(target),
                 level,
                 static_cast<GLint>(internal_format),
                 width, height,
                 0, // unused arg
                 static_cast<GLenum>(format),
                 static_cast<GLenum>(type),
                 data);
}

void Texture::generateMipmap(Texture::Target target) {
    Call::fast(glGenerateMipmap)(static_cast<GLuint>(target));
}

void Texture::setDepthStencilMode(Texture::Target target, Texture::DepthStencilMode mode) {
    Call::fast(glTexParameteri)(static_cast<GLenum>(target), GL_DEPTH_STENCIL_TEXTURE_MODE, static_cast<GLint>(mode));
}

void Texture::setMinFilter(Texture::Target target, Texture::MinFilter filter_mode) {
    Call::fast(glTexParameteri)(static_cast<GLenum>(target), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter_mode));
}

void Texture::setMaxFilter(Texture::Target target, Texture::MaxFilter max_filter) {
    Call::fast(glTexParameteri)(static_cast<GLenum>(target), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(max_filter));
}

void Texture::setWrapMode(Texture::Target target, Texture::WrapAxis axis, Texture::WrapMode mode) {
    Call::fast(glTexParameteri)(static_cast<GLenum>(target), static_cast<GLenum>(axis), static_cast<GLint>(mode));
}

void Texture::setActive(GLubyte i) {
    Call::fast(glActiveTexture)(GL_TEXTURE0 + i);
}


} // namespace Folk::gl
