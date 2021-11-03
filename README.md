# Folk Engine
CC5512 - Arquitectura de Motores de Juegos

Segundo semestre de 2021

## Resumen

Folk Engine es un motor para juegos de tipo RTS, city builder o colony sim. El foco de este proyecto es simulaciones con grandes cantidades de agentes capaces de interactuar entre sí y con el terreno.

### ¿Cómo funciona?

Incluir el header `folk/folk.hpp`. Ahí se declaran dos funciones que 
obligatoriamente deben ser implementadas por el usuario para poder compilar un
programa.

```cpp
void Folk::engineInit() {
    // Ajustar configuración global del engine.
    // Ejemplo: cambiar el nombre de la ventana
    Folk::Engine::setWindowTitle("Hello world!");
}

void Folk::sceneInit(Scene &scene) {
    // crear objetos, añadir components, etc.
    doSomething(scene);
}
```

Para modificar la escena en cada frame, es necesario establecer un callback:

```cpp
void onUpdate(Scene &scene, double delta);

void Folk::sceneInit(Scene &scene) {
    scene.updateCallback = onUpdate;
}
```

El callback será invocado con la escena y la cantidad de tiempo (en segundos) 
desde el último cuadro como argumentos.

Para un ejemplo más completo ver `examples/basic_setup.cpp`.

## Compilación y ejecución

Este proyecto fue desarrollado en Linux (Ubuntu 21.04). El sistema de build es CMake.

### Dependencias

#### OpenGL
El motor de renderizado utiliza algunas funcionalidades de OpenGL 4.3, por lo que es necesario tener drivers/hardware que lo soporte.

#### Doxygen
Es necesario tener instalado Doxygen para poder generar la documentación.

### Compilación

1. Descargar dependencias del proyecto 
```sh
git submodule update --init --recursive
```

2. Generar build
```sh
mkdir build
cd build
cmake ..
```

3. Compilar
```sh
cmake --build build -t <target>
```
O directamente con `make`:
```sh
cd build
make <target>
```
Las targets son:
- `folk_engine`: librería estática.
- `folk_docs`: documentación en html. Abrir con un navegador web, ej. `firefox build/html/index.html`.
- `basic_setup`: programa de ejemplo (`examples/basic_setup`).

#### Shaders
Este motor utiliza la librería gráfica BGFX. Para utilizar shaders distintos de los predeterminados, es necesario que estén escritos en el formato que esta librería requiere (una variante de GLSL) y que además hayan sido preprocesados con el compilador apropiado. Para facilitar este proceso, el proyecto en CMake incluye la función `folk_add_shader` que realiza la compilación.

El siguiente ejemplo crea targets que compilan los shaders antes de compilar el programa:

```{cmake}
# shaders
folk_add_shader(vert_shader vert.sc VERTEX "${CMAKE_CURRENT_BINARY_DIR}/shaders/vert.bin")

folk_add_shader(frag_shader frag.sc FRAGMENT "$}{CMAKE_CURRENT_BINARY_DIR}/shaders/frag.bin")

add_custom_target(shader_target)
add_dependencies(shader_target vert_shader frag_shader)

# ejecutable
add_executable(example_target example.cpp)
target_link_libraries(example_target folk_engine)

# compilar ejecutable + shaders
add_custom_target(example_with_shaders ALL)
add_dependencies(example_with_shaders example_target shader_target)
```

Además, los targets `vert_shader` y `frag_shader` pueden ser utilizados individualmente para preprocesar de nuevo los shaders. Los archivos `vert.bin` y `frag.bin` son los que la función `Folk::Shader::createFromFiles()` espera.