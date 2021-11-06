#include "folk/scene/transform_component.hpp"
#include "folk/scene/node.hpp"

#include "node_template_functions.hpp"

#include "bx/math.h"

namespace Folk
{

template TransformComponent& Node::addComponent();

template TransformComponent& Node::getComponent();

template TransformComponent* Node::tryGetComponent();

float* TransformComponent::modelMatrix() {
    bx::mtxTranslate(m_model_mtx, x, y, z);
    return m_model_mtx;
}

} // namespace Folk
