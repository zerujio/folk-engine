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