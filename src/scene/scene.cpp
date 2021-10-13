#include "folk/scene/scene.hpp"

namespace Folk {

Node& Scene::addNode(const char* name)
{
    Node* new_node = new Node(_registry, name);
    _nodes.push_back(new_node);
    return *new_node;
}

Node& Scene::addNode()
{
    addNode("New Node");
}

Scene::NodeList const& Scene::nodes()
{
    return _nodes;
}

} // namespace folk