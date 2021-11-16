#ifndef FOLK_RENDER__CAMERA_COMPONENT_HPP
#define FOLK_RENDER__CAMERA_COMPONENT_HPP

#include "folk/scene/scene.hpp"
#include "folk/scene/component_ptr.hpp"
#include "folk/math/vector.hpp"

namespace Folk
{

class CameraPtr;

/// Determina la posición de la camara en la escena.
struct CameraComponent final {
    using ptr_type = CameraPtr;
    static constexpr const char* type_name = "Camera";

    float fovy = 60.0f;
    float near = 0.01f;
    float far  = 100.0f;

    bool active {false};
};

struct CameraPtr final : public ComponentPtr<CameraComponent> {

    using ComponentPtr::ComponentPtr;

    float& fovy() const {
        return ref.fovy;
    }

    float& near() const {
        return ref.near;
    }

    float& far() const {
        return ref.far;
    }

private:
    friend class Scene;
};

} // namespace Folk

#endif // FOLK_RENDER__CAMERA_COMPONENT_HPP