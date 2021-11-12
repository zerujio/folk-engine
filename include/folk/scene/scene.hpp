#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/entity_handle.hpp"

#include <vector>

namespace Folk
{

/// \~spanish \brief Una escena del juego.
/// \~english \brief A game scene.
class Scene final {
    friend class SceneModule;
    friend class Renderer;

public:
    Scene();

    using UpdateCallback = void (*)(Scene&, double);

    /// \~spanish Una función que se invocará en cada nuevo cuadro. \~english A function to be called whenever a new frame is drawn.
    UpdateCallback updateCallback {nullptr};

    /// \~spanish Obtiene el nodo raíz del grafo de escena. \~english Get the root node of this scene.
    EntityHandle root() {return {{m_registry, m_root}};}
    
private:
    entt::registry m_registry {};
    entt::entity m_root {m_registry.create()};
};

}// namespace folk::scene

#endif//SCENE__SCENE_HPP
