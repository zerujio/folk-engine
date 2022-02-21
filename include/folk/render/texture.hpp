#ifndef SRC_RENDER__TEXTURE_HPP
#define SRC_RENDER__TEXTURE_HPP

#include "folk/core/resource.hpp"
#include "gl.hpp"
#include "gl_texture.hpp"
#include "image.hpp"

#include <functional>

namespace Folk {

/**
 * @brief Base class for Textures.
 *
 * Derived classes are meant to implement the functionality necessary for the different OpenGL texture types.
 */
class BaseTexture : public Resource
{
    friend class Renderer;

public:

    using WrapMode = gl::Texture::WrapMode;

protected:
    /// Initialize the texture object to the given type (i.e. bind to the target).
    explicit BaseTexture(gl::Texture::Target type);

    [[nodiscard]] gl::Texture::Target target() const;

    void bind() const;

private:
    gl::TextureManager m_texture {};
    gl::Texture::Target m_target;
};


/**
 * @brief Implements OpenGL 1D texture. Usable with *sampler1D uniforms.
 *
 * IMPLEMENTATION PENDING
 */
class Texture1D final : public BaseTexture {};


/**
 * @brief 2D texture usable with *sampler2D uniforms.
 */
class Texture2D final : public BaseTexture {

public:

    /**
     * @brief Create a texture from an image.
     * @param image_2d A square 2D image. The Image can be safely destroyed afterwards.
     */
    explicit Texture2D(const Image& image_2d);

};


/**
 * @brief Implements OpenGL 3D texture. Usable with *sampler3D uniforms.
 *
 * IMPLEMENTATION PENDING
 */
class Texture3D final : public BaseTexture {};


/**
 * @brief Implements OpenGL cube map texture. Usable with *samplerCube uniforms.
 * IMPLEMENTATION PENDING
 */
class CubeMap final : public BaseTexture {};


/**
 * @brief Implements OpenGL 1D texture arrays. Usable with *sampler1DArray uniforms.
 * IMPLEMENTATION PENDING
 */
class Texture1DArray final : public BaseTexture {};


/**
 * @brief Implements OpenGL 2D texture arrays. Usable with *sampler2DArray uniforms.
 * IMPLEMENTATION PENDING
 */
class Texture2DArray final : public BaseTexture {};


/**
 * @brief Implements cube map arrays. Usable with *samplerCubeArray uniforms.
 * IMPLEMENTATION PENDING
 */
class CubeMapArray final : public BaseTexture {};


/**
 * @brief Implements texture buffers. Usable with *samplerBuffer uniforms.
 * IMPLEMENTATION PENDING
 */
class TextureBuffer final : public BaseTexture {};


/**
 * @brief Multisample texture. Usable with *sampler2DMS uniforms.
 * IMPLEMENTATION PENDING
 */
class Texture2DMultisample final : public BaseTexture {};


/**
 * @brief Multisample texture array. Usable with *sampler2DMSArray uniforms.
 * IMPLEMENTATION PENDING
 */
class Texture2DMultisampleArray final : public BaseTexture {};

} // namespace Folk

#endif //SRC_RENDER__TEXTURE_HPP
