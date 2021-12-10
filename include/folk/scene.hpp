#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/entity_handle.hpp"

#include "folk/render/camera_component.hpp"

#include <vector>

namespace Folk
{

/// \~spanish \brief Una escena del juego.
/// \~english \brief A game scene.
class Scene final {
    friend class SceneManager;
    friend class Renderer;

public:
    Scene();
    ~Scene();

    using UpdateCallback = void (*)(Scene&, double);

    /// \~spanish Una función que se invocará en cada nuevo cuadro. \~english A function to be called whenever a new frame is drawn.
    UpdateCallback updateCallback {nullptr};

    /// \~spanish Obtiene el nodo raíz del grafo de escena. \~english Get the root node of this scene.
    EntityHandle root() {return {{m_registry, m_root}};}

    /// Configura la cámara a usar.
    /**
     * \param camera Referencia a CameraComponent.
    */
    void setCamera(CameraPtr camera);

    /// Puntero a la cámara en uso.
    CameraPtr getCamera();
    
private:
    entt::registry m_registry {};
    entt::entity m_root {m_registry.create()};
    entt::entity m_camera {entt::null};

    void onDestroyCamera(entt::registry&, entt::entity);
};

}// namespace folk::scene

#endif//FOLK_SCENE__SCENE_HPP
