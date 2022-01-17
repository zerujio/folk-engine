#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/entity_handle.hpp"
#include "folk/render/camera_component.hpp"
#include "folk/input/input_registry.hpp"
#include "folk/input/connection.hpp"

#include <vector>

namespace Folk
{

/// \~spanish \brief Una escena del juego.
/// \~english \brief A game scene. Contains ALL relevant data.
class Scene final {
    friend class SceneManager;

public:
    Scene();
    ~Scene();
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;

    InputRegistryManager input {m_input_registry};

    using UpdateCallback = void (*)(Scene&, float);

    /// \~spanish Una función que se invocará en cada nuevo cuadro. \~english A function to be called whenever a new frame is drawn.
    UpdateCallback updateCallback {nullptr};

    /// \~spanish Obtiene el nodo raíz del grafo de escena. \~english Get the root node of this scene.
    EntityHandle root() {return {{m_entity_registry, m_root}};}

    /// Configura la cámara a usar.
    /**
     * \param camera Referencia a CameraComponent.
    */
    void setCamera(CameraPtr camera);

    /// Puntero a la cámara en uso.
    CameraPtr getCamera();

private:
    entt::registry m_entity_registry {};
    entt::entity m_root {m_entity_registry.create()};
    entt::entity m_camera {entt::null};

    InputRegistry m_input_registry {};

    void onDestroyCamera(const entt::registry&, entt::entity);
};


}// namespace folk::scene

#endif//FOLK_SCENE__SCENE_HPP
