//
// Created by sergio on 17-02-22.
//

#ifndef SRC_RENDER__IMAGE_HPP
#define SRC_RENDER__IMAGE_HPP

#include "folk/math/vector.hpp"
#include "folk/utils/deleter.hpp"

#include <string>
#include <memory>

namespace Folk {

class Image final {

public:
    /// Load image from a file.
    explicit Image(const char* file_name);
    explicit Image(const std::string& file_name);

    /**
     * @brief Access image buffer.
     * @return Pointer raw image data.
     */
    [[nodiscard]] const unsigned char* data() const;

    /// Image dimensions in pixels.
    [[nodiscard]] Vec2i dimensions() const;

    /// Number of color channels in the image.
    [[nodiscard]] int channels() const;

private:

    using byte = unsigned char;

    static void freeData(byte* data);

    Vec2i m_dims {};
    int m_channels {};
    std::unique_ptr<unsigned char, Deleter<freeData>> p_data;
};

} // namespace Folk

#endif //SRC_RENDER__IMAGE_HPP
