#include "folk/folk.hpp"
#include "folk/render.hpp"

using namespace Folk;

void Folk::sceneInit(Scene &scene) {

    ImmediateGeometry<PositionNormalTexCoordVertex> mesh {
        // vertices
        {
            {{-.5f, -.25f, .0f}, {}, {.0f, .0f}},
            {{.5f, -.25f, .0f}, {}, {.5f, .0f}},
            {{.0f, .5f, .0f}, {}, {.25f, .25f}}
        },
        //indices
        { 0, 1, 2 }
    };

    auto visual_c = scene.root().addComponent<VisualComponent>(Mesh::create(mesh));

    visual_c.visual()->getMaterial()->uniform("u_color").value<UniformType::fVec4>() = {.75f, .5f, .25f, 1.0f};
}

void Folk::engineInit() {
    Folk::Game::setWindowTitle("Triangle!");
    Folk::Game::setPerformanceMetricsEnabled(true);
}