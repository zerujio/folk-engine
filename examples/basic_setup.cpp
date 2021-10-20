#include "folk/folk.hpp"
#include "folk/input/input.hpp"
#include "folk/render/visual_component.hpp"

#include <iostream>

// Una acción para determinar si se deben mostrar las métricas de rendmiento.
static Folk::InputAction enable_metrics;

// Esta función es invocada en cada frame
static void update(Folk::Scene& scn, double delta) {
    // Ajustar el framerate:
    // 15 FPS
    if(Folk::getKey(Folk::Key::Num1) == Folk::InputState::Press) {
        Folk::Engine::setMinFrameTime(0.066);
    } 
    // 30
    else if(Folk::getKey(Folk::Key::Num2) == Folk::InputState::Press) {
        Folk::Engine::setMinFrameTime(0.033);
    }
    // 60
    else if(Folk::getKey(Folk::Key::Num3) == Folk::InputState::Press) {
        Folk::Engine::setMinFrameTime(0.016);
    }
    // 144
    else if(Folk::getKey(Folk::Key::Num4) == Folk::InputState::Press) {
        Folk::Engine::setMinFrameTime(0.007);
    }
    // Ilimitado
    else if(Folk::getKey(Folk::Key::Num0) == Folk::InputState::Press) {
        Folk::Engine::setMinFrameTime(0.0);
    }
}

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

    // Configurar las teclas que activan las metricas de rendimiento
    // (Alt derecho e izquierdo)
    enable_metrics.addBinding(Folk::Key::RightAlt);
    enable_metrics.addBinding(Folk::Key::LeftAlt);
    enable_metrics.addCallback(metricsCallback);
}
