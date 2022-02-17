//
// Created by sergio on 17-02-22.
//

#include "image.hpp"

#include <stb_image.h>

namespace Folk {


Image::Image(const char *file_name)
: p_data(stbi_load(file_name, &m_dims.x, &m_dims.y, &m_channels, 0))
{}

Image::Image(const std::string &file_name) : Image(file_name.c_str()) {}

const unsigned char *Image::data() const {
    return p_data.get();
}

Vec2i Image::dimensions() const {
    return m_dims;
}

int Image::channels() const {
    return m_channels;
}

void Image::freeData(Image::byte *data) {
    stbi_image_free(data);
}


} // namespace Folk
