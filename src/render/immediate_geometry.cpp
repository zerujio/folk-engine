#include "folk/render/immediate_geometry.hpp"

namespace Folk
{

ImmediateGeometry ImmediateGeometry::colorSquare() {
    return {
        {
            {  0.5f,  0.5f, 0.0f, 0xffFFffFF},
            {  0.5f, -0.5f, 0.0f, 0xffFFffFF},
            { -0.5f, -0.5f, 0.0f, 0xffFFffFF},
            { -0.5f,  0.5f, 0.0f, 0xffFFffFF}
        },
        {
            0,1,3,
            1,2,3
        }
    };
}
    
} // namespace folk
