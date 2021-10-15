#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/node.hpp"

#include <vector>

namespace Folk
{

/// A game scene.
class Scene final {
    friend class SceneModule;
    friend class RenderModule;

public:
    using UpdateCallback = void (*)(Scene&, double);

    /// A function to be called whenever a new frame is drawn.
    UpdateCallback updateCallback {nullptr};

    /// Get the root node of this scene.
    Node& rootNode() {return _root;}
    Node const& rootNode() const {return _root;}
    
private:
    Node _root {"Root"};
};

}// namespace folk::scene

#endif//SCENE__SCENE_HPP
