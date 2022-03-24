#include "folk/folk.hpp"
#include "folk/render.hpp"
#include "folk/script.hpp"
#include "folk/input.hpp"

#include <glm/glm.hpp>

using namespace Folk;

class SimpleScript : public Script {

    using Script::Script;

    float lin_speed = 1.0f;
    float rot_speed = 90.0f;

    void update(std::chrono::duration<float> delta) override {

        auto transform = this_entity.getComponent<TransformComponent>().value();
        
        Vec3 direction {};

        direction.y += Input::get(Key::W) == InputState::Press;
        direction.y -= Input::get(Key::S) == InputState::Press;
        direction.x += Input::get(Key::D) == InputState::Press;
        direction.x -= Input::get(Key::A) == InputState::Press;
        direction.z += Input::get(Key::R) == InputState::Press;
        direction.z -= Input::get(Key::F) == InputState::Press;

        if ( direction.x || direction.y || direction .z ) {
            direction = glm::normalize(direction);
            transform.position(transform.position() + direction * lin_speed * delta.count());
        }

        float rotation = Input::get(Key::E) == InputState::Press;
        rotation -= Input::get(Key::Q) == InputState::Press;

        if (rotation)
            transform.rotation(transform.rotation() + Vec3(0.0f, rotation * rot_speed * delta.count(), 0.0f));
    }

};

void Folk::sceneInit(Scene &scene) {

    ImmediateGeometry<PositionNormalTexCoordVertex> mesh {
        // vertices
        {
            {{-.5f, -.5f, .0f}, {}, {.0f, .0f}},
            {{.5f, -.5f, .0f}, {}, {1.0f, .0f}},
            {{.5f, .5f, .0f}, {}, {1.0f, 1.0f}},
            {{-.5f, .5f, .0f}, {}, {.0f, 1.0f}}
        },
        //indices
        { 0, 1, 2,
          2, 3, 0 }
    };

    auto visual_c = scene.root().addComponent<VisualComponent>(Mesh::create(mesh));
    auto mat = visual_c.visual()->getMaterial();
    mat->setShader(Shader::createDefault<PositionNormalTexCoordVertex>());
    mat->uniform<UniformType::fVec4>("u_color").value = {1.0f, 1.0f, 1.0f, 1.0f};

    Image img {"paper.jpg"};
    auto tex = std::make_shared<Texture<TextureType::Tex2D>>(img);

    mat->uniform<UniformType::sampler2D>("u_texture").p_texture = tex;

    scene.root().addComponent<ScriptComponent>().addScript<SimpleScript>();
}

void Folk::engineInit() {
    Folk::Game::setWindowTitle("Hello World!");
    Folk::Game::setPerformanceMetricsEnabled(true);
}