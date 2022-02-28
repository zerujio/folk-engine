#include "folk/render/texture.hpp"

#include <array>

namespace Folk {

Folk::BaseTexture::BaseTexture(gl::Texture::Target type)
: m_target(type)
{
    m_texture.bind(m_target);
}

gl::Texture::Target BaseTexture::target() const {
    return m_target;
}

void BaseTexture::bind() const {
    m_texture.bind(m_target);
}

// Texture2D

Texture2D::Texture(const Image &image_2d)
: BaseTexture(gl::Texture::Target::Tex2D)
{
    if (image_2d.dimensions().x != image_2d.dimensions().y)
        throw Error("Image width and height differ.");

    using IFormat = gl::Texture::InternalFormat;
    using Format = gl::Texture::Format;
    using Type = gl::Texture::Type;

    constexpr std::array<std::pair<IFormat, Format>, 4> a_formats {
            std::pair
            {IFormat::R8, Format::Red},
            {IFormat::RG8, Format::RG},
            {IFormat::RGB8, Format::RGB},
            {IFormat::RGBA8, Format::RGBA}
    };

    auto format = a_formats[image_2d.channels() - 1];

    gl::Texture::texImage2D(target(), 0,
                            format.first, image_2d.dimensions().x, image_2d.dimensions().y,
                            format.second, Type::UByte, image_2d.data());
    gl::Texture::generateMipmap(target());
}


/// Set the wrap mode of the texture (for both axis).
void Texture2D::setWrapMode(WrapMode mode) const {
    bind();
    gl::Texture::setWrapMode(gl::Texture::Target::Tex2D, gl::Texture::WrapAxis::S, mode);
    gl::Texture::setWrapMode(gl::Texture::Target::Tex2D, gl::Texture::WrapAxis::T, mode);
}

/// Set the texture wrap mode on the X axis.
void Texture2D::setWrapModeX(WrapMode mode) const {
    bind();
    gl::Texture::setWrapMode(gl::Texture::Target::Tex2D, gl::Texture::WrapAxis::S, mode);
}

/// Set the texture wrap mode on the Y axis.
void Texture2D::setWrapModeY(WrapMode mode) const {
    bind();
    gl::Texture::setWrapMode(gl::Texture::Target::Tex2D, gl::Texture::WrapAxis::T, mode);
}

} // namespace Folk