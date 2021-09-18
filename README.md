# Folk Engine
CC5512 - Arquitectura de Motores de Juegos

Segundo semestre de 2021

## Resumen

Folk Engine es un motor para juegos de tipo RTS, city builder o colony sim. El foco de este proyecto es simulaciones con grandes cantidades de agentes capaces de interactuar entre sí, y así como con el terreno.

### ¿Cómo funciona?

Incluir los headers necesarios. Definir la función `initScene` e inicializar la escena:

```cpp
void initScene(Scene &scene) {
    // crear objetos, añadir scripts, etc.
    scene.doSomething();
}
```