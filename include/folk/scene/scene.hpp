#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/node.hpp"

#include <vector>

namespace Folk
{

/// \~spanish \brief Una escena del juego.
/// \~english \brief A game scene.
class Scene final {
    friend class SceneModule;
    friend class Renderer;

public:
    using UpdateCallback = void (*)(Scene&, double);

    /// \~spanish Una función que se invocará en cada nuevo cuadro. \~english A function to be called whenever a new frame is drawn.
    UpdateCallback updateCallback {nullptr};

    /// \~spanish Obtiene el nodo raíz del grafo de escena. \~english Get the root node of this scene.
    Node& rootNode() {return _root;}
    Node const& rootNode() const {return _root;}
    
private:
    Node _root {"Root"};
};

}// namespace folk::scene

#endif//SCENE__SCENE_HPP
