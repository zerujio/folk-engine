#include "folk/folk.hpp"
#include "folk/input/input.hpp"
#include "folk/render/visual_component.hpp"
#include "folk/core/error.hpp"
#include "folk/core/log.hpp"

#include <iostream>

// Esta función se llama antes de inicializar la escena
void Folk::engineInit() {
    Folk::Engine::setWindowTitle("Hello world!");
    Folk::Engine::setPerformanceMetricsEnabled(true);
}

void metricsCallback(Folk::InputState state) {
    if (state == Folk::InputState::Press) {
        // se activan las métricas de rendimiento.
        Folk::Engine::setPerformanceMetricsEnabled(true);
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
        throw Folk::CriticalEngineError("Dummy critical error.");

    case Folk::Key::Space:
        throw Folk::EngineRuntimeError("Dummy runtime error.");
    }
}

void update(Folk::Scene& scn, double delta) {
    if (Folk::getMouseButton(Folk::MouseButton::Left) == Folk::InputState::Press)
        Folk::log(Folk::LogLevel::MESSAGE) << "dt=" << delta << '\n';
}

// Esta función se llama para inicializar la escena
void Folk::sceneInit(Folk::Scene &scene) {
    // Añadir un nuevo nodo como hijo del nodo raíz.
    Node& square = scene.rootNode().createChild("Square");

    // Crear una Visual...
    auto visual = Visual::create(
        Mesh::create(ImmediateGeometry::triangle()), // con un triangulo como mesh
        Material::createDefaultMaterial()            // y el shader default
    );

    // Añadir al nodo una componente con la Visual anterior
    auto& component = square.addComponent<VisualComponent>(visual);

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
