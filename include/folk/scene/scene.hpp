#ifndef FOLK_SCENE__SCENE_HPP
#define FOLK_SCENE__SCENE_HPP

#include "folk/scene/node.hpp"

#include <vector>

namespace folk
{

class Scene final {
    friend class SceneModule;
    friend class RenderModule;

public:
    using UpdateCallback = void (*)(Scene&, double);

    /// A function to be called whenever a new frame is drawn.
    UpdateCallback updateCallback {nullptr};

    /// Create a new node in the scene.
    Node& addNode(const char* name);
    Node& addNode();

    using NodeList = std::vector<Node*>;

    /// The list of all nodes in the scene.
    NodeList const& nodes();
    
private:
    NodeList _nodes {};
    entt::registry _registry;
};

}// namespace folk::scene

#endif//SCENE__SCENE_HPP
