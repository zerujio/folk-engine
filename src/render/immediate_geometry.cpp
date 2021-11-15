#include "folk/render/immediate_geometry.hpp"

namespace Folk
{

ImmediateGeometry ImmediateGeometry::createCube(const uint32_t color) {
    return {
        {
            {-1.0f,  1.0f,  1.0f, color },
            { 1.0f,  1.0f,  1.0f, color },
            {-1.0f, -1.0f,  1.0f, color },
            { 1.0f, -1.0f,  1.0f, color },
            {-1.0f,  1.0f, -1.0f, color },
            { 1.0f,  1.0f, -1.0f, color },
            {-1.0f, -1.0f, -1.0f, color },
            { 1.0f, -1.0f, -1.0f, color },
        },
        {
            0, 1, 2,
            1, 3, 2,
            4, 6, 5,
            5, 6, 7,
            0, 2, 4,
            4, 2, 6,
            1, 5, 3,
            5, 7, 3,
            0, 4, 1,
            4, 5, 1,
            2, 3, 6,
            6, 3, 7,
        }
    };
}
    
} // namespace folk
