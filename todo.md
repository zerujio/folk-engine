Documentación:

- [ ] Mantener actualizada la documentación.


API:

- [x] (0.6) API separada de la implementación de bajo nivel.
- [ ] (0.9) Utilidades para RTS:
  - [ ] Control de cámara top-down (script?).
  - [ ] (opcional) Cámara isométrica.
  - [ ] (opcional) seleccionar objetos mediante un click.


GameObject model:

- [x] (0.6) Entity-Component System 
  - [x] Creación/destrucción de entidades en tiempo de ejecución.
  - [x] Actualización de sistemas y entidades.


Manejo de tiempo:

- [x] (0.3)
  - [x] Frame time mínimo / frame rate máximo
  - [x] Delta máximo (0.5ms)
  - [x] Contador de FPS


Input:

- [x] (0.3)
  - [x] Uso de mouse y teclado.
  - [x] Capa de abstracción.
- [x] (0.3) Remapping


Scripting

- [x] (0.3) scripting nativo
- [ ] (0.6) lenguaje de scripting (i.e Lua), con al menos dos de las siguientes funcionalidades:
  - [ ] Máquinas de estado finitas
  - [ ] Callbacks de código nativo a scripts
  - [ ] Callbacks de scripts a código nativo
  - [ ] Sistema de eventos
  - [ ] Creación/modificación de entidades


Rendering

- [x] (0.3) Al menos uno de los siguientes:
  - [ ] Sistema de manejo de sprites
  - [x] Sistema de manejo de meshes (falta agregar assimp).
  - [ ] Sistema de renderizado de texto
- [ ] (0.6) Alguna optimización básica:
  - [ ] Clipping
  - [ ] Grafo de escena para determinación de visibilidad
- [ ] (0.9) Optimización avanzada, utilidades
  - [ ] rendimiento superior a 30fps en hardware equipo docente
  - [ ] Utilidades: renderizado de mapas?
- [ ] (bonus?) Instanced rendering


Audio

- [x] (0.6) Audio 2D, múltiples fuentes sonoras estáticas.
- [x] (0.9) Audio 3D, múltiples fuentes sonoras estáticas y dinámicas.


Física/Colisiones:

- [ ] (0.3) detección de colisiones basado en AABB o distancias.

Behavior Trees:
- [ ] (0.6) Implementación simple de behavior tree, con ejemplo.



DEMO 

- [ ] (0.8) debe utilizar
  - [ ] Input, remapping
  - [ ] Utilidades de cámara
  - [ ] Scripting
  - [ ] Detección de colisiones
  - [ ] IA con behavior trees

- [ ] (1.0) mecánicas básicas (al menos dos):
  - Seleccionar unidad haciendo click.
  - Dar órdenes a unidad seleccionada.
  - Poner construcciones estilo SimCity?