#include "folk/render/mesh.hpp"

#include "../core/engine.hpp"

#include "renderer.hpp"

namespace Folk
{

DrawMode Mesh::getDrawMode() const {
    return m_draw_mode;
}

void Mesh::setDrawMode(DrawMode draw_mode) {
    m_draw_mode = draw_mode;
}

std::shared_ptr<Mesh> Mesh::createCube(const Color color) {

    std::array<PositionColorVertex, 8> vertices {
            PositionColorVertex
            { {-1.0f,  1.0f,  1.0f}, color },
            { { 1.0f,  1.0f,  1.0f}, color },
            { {-1.0f, -1.0f,  1.0f}, color },
            { { 1.0f, -1.0f,  1.0f}, color },
            { {-1.0f,  1.0f, -1.0f}, color },
            { { 1.0f,  1.0f, -1.0f}, color },
            { {-1.0f, -1.0f, -1.0f}, color },
            { { 1.0f, -1.0f, -1.0f}, color }
    };

    std::array<GLuint, 36> indices {
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
    };

    return std::make_shared<Mesh>( vertices, indices, DrawMode::Triangles );
}

} // namespace folk
