//
// Created by sergio on 17-02-22.
//

#include "folk/render/texture.hpp"

#include <array>

namespace Folk {

Folk::BaseTexture::BaseTexture(gl::Texture::Target type)
: m_target(type)
{
    m_texture.bind(type);
}

gl::Texture::Target BaseTexture::target() const {
    return m_target;
}

void BaseTexture::bind() const {
    m_texture.bind(m_target);
}

// Texture2D

Texture2D::Texture2D(const Image &image_2d)
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

} // namespace Folk