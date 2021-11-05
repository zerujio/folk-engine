#ifndef FOLK_RENDER__VISUAL_COMPONENT
#define FOLK_RENDER__VISUAL_COMPONENT

#include "folk/render/visual.hpp"

namespace Folk {

/// Determina cómo se dibuja un objeto.
/**
 * \see Visual
*/
class VisualComponent final {
public:

    /// Visual que determina el material y la malla.
    std::shared_ptr<Visual> visual;

    /// Construye un componente con una malla vacía y el shader predeterminado.
    VisualComponent() : visual(Visual::create()) {}

    /// Construye un nuevo componente que utiliza el Visual referenciado.
    VisualComponent(std::shared_ptr<Visual> visual_) : visual(visual_) {}
};

}// namespace folk

#endif//FOLK_RENDER__VISUAL_COMPONENT