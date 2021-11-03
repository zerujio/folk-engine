#include "folk/render/immediate_geometry.hpp"

namespace Folk
{

ImmediateGeometry ImmediateGeometry::colorSquare() {
    return {
        {
            {  0.5f,  0.5f, 0.0f, 0xff, 0x00, 0x00, 0xff },
            {  0.5f, -0.5f, 0.0f, 0x00, 0xff, 0x00, 0xff },
            { -0.5f, -0.5f, 0.0f, 0x00, 0x00, 0xff, 0xff },
            { -0.5f,  0.5f, 0.0f, 0xff, 0x00, 0xff, 0xff }
        },
        {
            0,1,3,
            1,2,3
        }
    };
}
    
} // namespace folk
