#ifndef FOLK_RENDER__VISUAL_COMPONENT
#define FOLK_RENDER__VISUAL_COMPONENT

#include "folk/render/visual.hpp"
#include "folk/scene/node.hpp"

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

    static VisualComponent& emplaceComponent(const Node::Id);
    static VisualComponent& emplaceComponent(const Node::Id, 
                                             std::shared_ptr<Visual>);
    static VisualComponent* getComponent(const Node::Id);
    static bool removeComponent(const Node::Id);
};

}// namespace folk

#endif//FOLK_RENDER__VISUAL_COMPONENT