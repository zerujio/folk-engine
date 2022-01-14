#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/entity_handle.hpp"
#include "folk/render/camera_component.hpp"
#include "folk/input/input_event_dispatcher.hpp"
#include "folk/input/input_event_manager.hpp"
#include "folk/input/input_action_registry.hpp"
#include "folk/input/input_action_manager.hpp"
#include "folk/input/connection.hpp"

#include <vector>

namespace Folk
{

/// \~spanish \brief Una escena del juego.
/// \~english \brief A game scene. Contains ALL relevant data.
class Scene final {
    friend class SceneManager;

    struct InputDispatcher;

public:
    Scene();
    ~Scene();
    Scene(Scene&&) = default;
    Scene& operator=(Scene&&) = default;

    class InputManager final {

        friend class Scene;

        explicit InputManager(InputDispatcher& dispatcher)
        : events(dispatcher.event_dispatcher), actions(dispatcher.action_registry)
        {}

    public:
        InputEventManager events;
        InputActionManager actions;
    };

    InputManager input {m_input_dispatcher};

    using UpdateCallback = void (*)(Scene&, float);

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

    class InputDispatcher final {

        friend class Scene::InputManager;

        InputEventDispatcher event_dispatcher {};
        InputActionRegistry action_registry {};

    public:
        InputDispatcher();

        /// Enqueue an input event.
        template<class InputType>
        void enqueue(InputType code, InputState state) {
            event_dispatcher.template enqueue(code, state);
        }

        /// Process all queued input events.
        void update(const ExceptionHandler& handler) noexcept;
    };

    entt::registry m_registry {};
    entt::entity m_root {m_registry.create()};
    entt::entity m_camera {entt::null};

    InputDispatcher m_input_dispatcher {};

    void onDestroyCamera(const entt::registry&, entt::entity);
};


}// namespace folk::scene

#endif//FOLK_SCENE__SCENE_HPP
