#ifndef FOLK_RENDER__VISUAL_COMPONENT
#define FOLK_RENDER__VISUAL_COMPONENT

#include "folk/render/common.hpp"
#include "folk/render/visual.hpp"

namespace Folk {

/// Determines how an object is to be drawn.
/**
 * @see Visual
*/
class VisualComponent {
public:

    /// Reference to a Visual resource.
    Visual::Ref visual;

    /// Construct a mesh component with an empty mesh.
    VisualComponent() 
        : VisualComponent(
            Visual::create( Mesh::createEmpty(),
                            Material::createDefaultMaterial() )
            )
    {}

    /// Construct a component from the given Visual.
    VisualComponent(Visual::Ref const& v) : visual(v) {}
};

}// namespace folk

#endif//FOLK_RENDER__VISUAL_COMPONENT