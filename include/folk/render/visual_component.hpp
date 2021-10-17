#ifndef FOLK_RENDER__VISUAL_COMPONENT
#define FOLK_RENDER__VISUAL_COMPONENT

#include "folk/render/common.hpp"
#include "folk/render/visual.hpp"

namespace Folk {

/// \~spanish Determina cómo se dibuja un objeto. \~english Determines how an object is to be drawn.
/**
 * \see Visual
*/
class VisualComponent {
public:

    /// \~spanish Visual que determina el material y la malla. Reference to a Visual resource.
    Visual::Ref visual;

    /// \~spanish Construye un componente con una malla vacía y el shader predeterminado. \~english Construct a mesh component with an empty mesh.
    VisualComponent() 
        : VisualComponent(
            Visual::create( Mesh::createEmpty(),
                            Material::createDefaultMaterial() )
            )
    {}

    /// \~spanish Construye un nuevo componente que utiliza el Visual referenciado. \~english Construct a component from the given Visual.
    VisualComponent(Visual::Ref const& v) : visual(v) {}
};

}// namespace folk

#endif//FOLK_RENDER__VISUAL_COMPONENT