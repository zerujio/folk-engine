#ifndef SRC_RENDER__TEXTURE_HPP
#define SRC_RENDER__TEXTURE_HPP

#include "folk/core/resource.hpp"
#include "gl.hpp"
#include "gl_texture.hpp"
#include "image.hpp"
#include "uniform_type.hpp"

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
    template<class> friend class Uniform;

public:

protected:
    /// Initialize the texture object to the given type (i.e. bind to the target).
    explicit BaseTexture(gl::Texture::Target type);

    void bind() const;

    [[nodiscard]] gl::Texture::Target target() const;

private:
    gl::TextureManager m_texture {};
    gl::Texture::Target m_target;
};

using TextureType = gl::Texture::Target;

template<TextureType Type> class Texture;

/**
 * @brief Implements OpenGL 1D texture. Usable with *sampler1D uniforms.
 *
 * IMPLEMENTATION PENDING
 */
template<> class Texture<TextureType::Tex1D> final : public BaseTexture {};
using Texture1D = Texture<TextureType::Tex1D>;


/**
 * @brief 2D texture usable with *sampler2D uniforms.
 */
template<>
class Texture<TextureType::Tex2D> final : public BaseTexture {

public:

    /**
     * @brief Create a texture from an image.
     * @param image_2d A square 2D image. The Image can be safely destroyed afterwards.
     */
    explicit Texture(const Image& image_2d);

    using WrapMode = gl::Texture::WrapMode;

    /// Set the wrap mode of the texture (for both axis).
    void setWrapMode(WrapMode mode) const;

    /// Set the texture wrap mode on the X axis.
    void setWrapModeX(WrapMode mode) const;

    /// Set the texture wrap mode on the Y axis.
    void setWrapModeY(WrapMode mode) const;

};
using Texture2D = Texture<TextureType::Tex2D>;


/**
 * @brief Implements OpenGL 3D texture. Usable with *sampler3D uniforms.
 *
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::Tex3D> final : public BaseTexture {};
using Texture3D = Texture<TextureType::Tex3D>;


/**
 * @brief 2D rectangular (i.e. not necessarily square) texture. Usable with *sampler2DRect uniforms.
 */
template<>
class Texture<TextureType::Rectangle> final : public BaseTexture {};
using Texture2DRect = Texture<TextureType::Rectangle>;


/**
 * @brief Implements OpenGL cube map texture. Usable with *samplerCube uniforms.
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::CubeMap> final : public BaseTexture {};
using CubeMap = Texture<TextureType::CubeMap>;


/**
 * @brief Implements OpenGL 1D texture arrays. Usable with *sampler1DArray uniforms.
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::Tex1DArray> final : public BaseTexture {};
using Texture1DArray = Texture<TextureType::Tex1DArray>;


/**
 * @brief Implements OpenGL 2D texture arrays. Usable with *sampler2DArray uniforms.
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::Tex2DArray> final : public BaseTexture {};
using Texture2DArray = Texture<TextureType::Tex2DArray>;

/**
 * @brief Implements cube map arrays. Usable with *samplerCubeArray uniforms.
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::CubeMapArray> final : public BaseTexture {};
using CubeMapArray = Texture<TextureType::CubeMapArray>;


/**
 * @brief Implements texture buffers. Usable with *samplerBuffer uniforms.
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::TexBuffer> final : public BaseTexture {};
using TextureBuffer = Texture<TextureType::TexBuffer>;

/**
 * @brief Multisample texture. Usable with *sampler2DMS uniforms.
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::Tex2DMultisample> final : public BaseTexture {};
using Texture2DMultisample = Texture<TextureType::Tex2DMultisample>;

/**
 * @brief Multisample texture array. Usable with *sampler2DMSArray uniforms.
 * IMPLEMENTATION PENDING
 */
template<>
class Texture<TextureType::Tex2DMultisampleArray> final : public BaseTexture {};
using Texture2DMultisampleArray = Texture<TextureType::Tex2DMultisampleArray>;


namespace impl {

// binds UniformType enum values to the appropriate Texture types


FOLK_UNIFORM_TYPE_REP_DEF(sampler1D,        Texture1D)
FOLK_UNIFORM_TYPE_REP_DEF(sampler1DArray,   Texture1DArray)
FOLK_UNIFORM_TYPE_REP_DEF(sampler2D,        Texture2D)
FOLK_UNIFORM_TYPE_REP_DEF(sampler2DArray,   Texture2DArray)
FOLK_UNIFORM_TYPE_REP_DEF(sampler2DRect,    Texture2DRect)
FOLK_UNIFORM_TYPE_REP_DEF(sampler2DMS,      Texture2DMultisample)
FOLK_UNIFORM_TYPE_REP_DEF(sampler2DMSArray, Texture2DMultisampleArray)
FOLK_UNIFORM_TYPE_REP_DEF(sampler3D,        Texture3D)
FOLK_UNIFORM_TYPE_REP_DEF(samplerCube,      CubeMap)
FOLK_UNIFORM_TYPE_REP_DEF(samplerBuffer,    TextureBuffer)

} //

} // namespace Folk

#endif //SRC_RENDER__TEXTURE_HPP
