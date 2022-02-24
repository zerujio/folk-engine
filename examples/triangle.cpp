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
    auto mat = visual_c.visual()->getMaterial();

    mat->uniform<UniformType::fVec4>("u_color").value = {.75f, .5f, .25f, 1.0f};

    Image img {"paper.jpg"};
    auto tex = std::make_shared<Texture<TextureType::Tex2D>>(img);

    mat->uniform<UniformType::sampler2D>("u_texture").p_texture = tex;
}

void Folk::engineInit() {
    Folk::Game::setWindowTitle("Triangle!");
    Folk::Game::setPerformanceMetricsEnabled(true);
}