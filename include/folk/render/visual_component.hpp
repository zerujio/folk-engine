#ifndef FOLK_RENDER__VISUAL_COMPONENT
#define FOLK_RENDER__VISUAL_COMPONENT

#include "folk/render/visual.hpp"
#include "folk/scene/entity_handle.hpp"
#include "folk/scene/component_ptr.hpp"

namespace Folk {

struct VisualPtr;

/// Determina cómo se dibuja un objeto.
/**
 * \see Visual
 * \see VisualPtr
*/
struct VisualComponent final {
    using ptr_type = VisualPtr;
    static constexpr const char* type_name = "Visual";

    /// Visual que determina el material y la malla.
    std::shared_ptr<Visual> visual {Visual::create()};

    /// Construye un componente con una malla vacía y el shader predeterminado.
    VisualComponent() = default;

    /// Construye un nuevo componente que utiliza el Visual referenciado.
    VisualComponent(std::shared_ptr<Visual> visual_) : visual(visual_) {}
};

class VisualPtr final : public ComponentPtr<VisualComponent> {
public:
    using ComponentPtr::ComponentPtr;

    std::shared_ptr<Visual>& visual() { return ref.visual; }

    void setVisual(std::shared_ptr<Visual>& v) { ref.visual = v; }
};

}// namespace folk

#endif//FOLK_RENDER__VISUAL_COMPONENT