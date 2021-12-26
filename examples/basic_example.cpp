#include "folk/folk.hpp"
#include "folk/scene/transform_component.hpp"
#include "folk/input.hpp"
#include "folk/render/visual_component.hpp"
#include "folk/error.hpp"
#include "folk/log.hpp"

// Esta función se llama antes de inicializar la escena
void Folk::engineInit() {
    Folk::Engine::setWindowTitle("Hello world!");
    Folk::Engine::setPerformanceMetricsEnabled(true);
}

void metricsCallback(Folk::InputState state) {
    static bool show = true;

    if (state == Folk::InputState::Press) {
        // se activan las métricas de rendimiento.
        show = !show;
        Folk::Engine::setPerformanceMetricsEnabled(show);
    }
}

void keyCallback(Folk::Key key, Folk::InputState state) {
    if (state == Folk::InputState::Press)
        return;
    
    switch (key)
    {
    case Folk::Key::Num1:
        // 15 fps
        Folk::Engine::setMinFrameTime(0.066);
        break;

    case Folk::Key::Num2:
        // 30
        Folk::Engine::setMinFrameTime(0.033);
        break;

    case Folk::Key::Num3:
        // 60
        Folk::Engine::setMinFrameTime(0.016);
        break;

    case Folk::Key::Num4:
        // 144
        Folk::Engine::setMinFrameTime(0.007);
        break;

    case Folk::Key::Num0:
        // ilimitado
        Folk::Engine::setMinFrameTime(0.0);
        break;

    case Folk::Key::Escape:
        using Folk::CriticalError;
        throw FOLK_CRITICAL_ERROR("Dummy critical error.");

    case Folk::Key::Space:
        using Folk::RuntimeError;
        throw FOLK_RUNTIME_ERROR("Dummy runtime error");

    default:
        break;
    }
}

void update(Folk::Scene& scn, float delta) {
    if (Folk::getMouseButton(Folk::MouseButton::Left) == Folk::InputState::Press)
        // Para poder ver este mensaje el programa debe iniciarse con la opción "-l trace"
        Folk::Log::trace() << "dt=" << delta << '\n';

    auto node = scn.root().getChild("Square");
    auto tr = *(node->getComponent<Folk::TransformComponent>());

    float spd = 1.5f;
    float dist = spd * delta;

    // Mover el cubo en la escena
    {
        auto pos = tr.position();

        if (Folk::getKey(Folk::Key::W) == Folk::InputState::Press) {
            pos.y += dist;
        }

        if (Folk::getKey(Folk::Key::S) == Folk::InputState::Press) {
            pos.y -= dist;
        }

        if (Folk::getKey(Folk::Key::D) == Folk::InputState::Press) {
            pos.x += dist;
        }

        if (Folk::getKey(Folk::Key::A) == Folk::InputState::Press) {
            pos.x -= dist;
        }

        if (tr.position() != pos)
            tr.position(pos);
    }

    // Rotar el cubo
    {
        auto rot = tr.rotation();

        if (Folk::getKey(Folk::Key::Q) == Folk::InputState::Press) {
            rot.y -= dist;
        }
        if (Folk::getKey(Folk::Key::E) == Folk::InputState::Press) {
            rot.y += dist;
        }

        if (rot != tr.rotation())
            tr.rotation(rot);
    }

    // Ajustar el fov de la cámara
    {
        auto camera = scn.getCamera();

        if (Folk::getKey(Folk::Key::R) == Folk::InputState::Press) {
            camera.fovy() += dist * 10.0f;
        }

        if (Folk::getKey(Folk::Key::F) == Folk::InputState::Press) {
            camera.fovy() -= dist * 10.0f;
        }
    }
}

// Esta función se llama para inicializar la escena
void Folk::sceneInit(Folk::Scene &scene) {
    // Añadir un nuevo nodo como hijo del nodo raíz.
    EntityHandle cube = scene.root().createChild("Square");

    // cargamos un shader
    //auto shader = Shader::createFromFiles("vs_basic.bin", "fs_basic.bin");
    auto shader = Shader::createDefault();

    // Crear una Visual...
    auto visual = Visual::create(
        Mesh::create(ImmediateGeometry::createCube(0xffffffff)), // con un cuadrado como mesh
        Material::create(shader)    // y el shader que leímos desde el archivo
    );

    // Añadir al nodo una componente con la Visual anterior
    cube.addComponent<VisualComponent>(visual);

    // Añadir un cubo más pequeño, como nodo hijo.
    auto small_cube = cube.createChild("Small Cube");

    auto small_cube_tr = *small_cube.getComponent<TransformComponent>();
    small_cube_tr.scale({0.5f, 0.5f, 0.5f});
    small_cube_tr.position({1.0f, 1.0f, 1.0f});

    auto small_visual = Visual::create(
        Mesh::create(ImmediateGeometry::createCube(0xff0000ff)),
        visual->getMaterial()
    );
    small_cube.addComponent<VisualComponent>(small_visual);

    // Añadir una cámara
    auto cam = scene.root().createChild("Camera");
    auto cam_component = cam.addComponent<CameraComponent>();
    cam.getComponent<TransformComponent>()->position({0.0f, 0.0f, -5.0f});

    scene.setCamera(cam_component);
   
    // Configurar el callback que se invocará en cada frame
    scene.updateCallback = update;

    // Una acción para determinar si se deben mostrar las métricas de rendmiento.
    auto &enable_metrics = Folk::InputAction::create("enable_metrics");

    // Configurar las teclas que activan las metricas de rendimiento
    // (Alt derecho e izquierdo)
    enable_metrics.addBinding(Folk::Key::RightAlt);
    enable_metrics.addBinding(Folk::Key::LeftAlt);
    enable_metrics.addCallback(metricsCallback);

    addKeyCallback(keyCallback);
}
