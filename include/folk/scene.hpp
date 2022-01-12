#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/entity_handle.hpp"
#include "folk/render/camera_component.hpp"
#include "folk/input/input_event_dispatcher.hpp"
#include "folk/input/input_action_registry.hpp"

#include <vector>

namespace Folk
{

using Connection = entt::connection;
using ScopedConnection = entt::scoped_connection;

/// \~spanish \brief Una escena del juego.
/// \~english \brief A game scene. Contains ALL relevant data.
class Scene final {
    friend class SceneManager;

    struct InputManager final {
        InputEventDispatcher event_dispatcher {};
        InputActionRegistry action_registry {};
    };

    entt::registry m_registry {};
    entt::entity m_root {m_registry.create()};
    entt::entity m_camera {entt::null};

    InputManager m_input_manager {};

    Scene& operator=(Scene&&) = default;

    void onDestroyCamera(const entt::registry&, entt::entity);

public:

    InputEventDispatcher::ConnectionManager input_event {m_input_manager.event_dispatcher};
    InputActionManager input_action {m_input_manager.action_registry};

    using UpdateCallback = void (*)(Scene&, float);
    /// \~spanish Una función que se invocará en cada nuevo cuadro. \~english A function to be called whenever a new frame is drawn.
    UpdateCallback updateCallback {nullptr};

    Scene();
    ~Scene();

    /// \~spanish Obtiene el nodo raíz del grafo de escena. \~english Get the root node of this scene.
    EntityHandle root() {return {{m_registry, m_root}};}

    /// Configura la cámara a usar.
    /**
     * \param camera Referencia a CameraComponent.
    */
    void setCamera(CameraPtr camera);

    /// Puntero a la cámara en uso.
    CameraPtr getCamera();
};

}// namespace folk::scene

#endif//FOLK_SCENE__SCENE_HPP
