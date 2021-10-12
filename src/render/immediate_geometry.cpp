#include "folk/render/immediate_geometry.hpp"

namespace folk
{

ImmediateGeometry ImmediateGeometry::triangle() {
    return ImmediateGeometry(
        {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
        },
        {0, 1, 3,
         1, 2, 3}
    );
}

ImmediateGeometry ImmediateGeometry::rainbowTriangle() {
    return ImmediateGeometry(
        // vertices
        {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
        },
        // indices
        {0, 1, 2}
    );
}
    
} // namespace folk
