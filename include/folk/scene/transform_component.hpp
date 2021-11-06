#ifndef FOLK_SCENE__TRANSFORM_COMPONENT_HPP
#define FOLK_SCENE__TRANSFORM_COMPONENT_HPP

namespace Folk
{

class TransformComponent {
public:
    float x {0};
    float y {0};
    float z {0};

    float* modelMatrix();

private:
    float m_model_mtx[16];
};

} // namespace Folk


#endif // FOLK_SCENE__TRANSFORM_COMPONENT_HPP