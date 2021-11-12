#ifndef FOLK_RENDER__VISUAL_COMPONENT
#define FOLK_RENDER__VISUAL_COMPONENT

#include "folk/render/visual.hpp"
#include "folk/scene/entity_handle.hpp"

namespace Folk {

/// Determina cómo se dibuja un objeto.
/**
 * \see Visual
*/
class VisualComponent final {
public:
    static constexpr const char* type_name = "Visual";

    /// Visual que determina el material y la malla.
    std::shared_ptr<Visual> visual;

    /// Construye un componente con una malla vacía y el shader predeterminado.
    VisualComponent() : visual(Visual::create()) {}

    /// Construye un nuevo componente que utiliza el Visual referenciado.
    VisualComponent(std::shared_ptr<Visual> visual_) : visual(visual_) {}

    static VisualComponent& emplaceComponent(const entt::handle);
    static VisualComponent& emplaceComponent(const entt::handle, 
                                             std::shared_ptr<Visual>);
    static VisualComponent* getComponent(const entt::handle);
    static bool removeComponent(const entt::handle);
};

}// namespace folk

#endif//FOLK_RENDER__VISUAL_COMPONENT