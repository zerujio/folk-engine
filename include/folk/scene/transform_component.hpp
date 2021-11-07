#ifndef FOLK_SCENE__TRANSFORM_COMPONENT_HPP
#define FOLK_SCENE__TRANSFORM_COMPONENT_HPP

#include <folk/utils/vector.hpp>

namespace Folk
{

/// Determina la posición y orientación de un objeto (Node) en la escena.
/**
 * Todos los nodos se crean con una componente Transform, y esta no puede ser
 * quitada.
*/
class TransformComponent {
public: 
    /// Consulta la posición.
    const Vec3f& position() const;

    /// Modifica la posición;
    void position(const Vec3f&);

    /// Consulta la rotación
    const Vec3f& rotation() const;
    
    /// Modifica la rotación.
    void rotation(const Vec3f&);

    /// Consulta la escala.
    const Vec3f& scale() const;

    /// Modifica la escala;
    void scale(const Vec3f&);

    struct Matrix;

    const Matrix& localMatrix() const;

    struct Matrix {
        Matrix();
        operator float*(){
            return m_arr;
        }
        operator const float*() const {
            return m_arr;
        }
    private:
        float m_arr[16];
    };
private:
    Vec3f m_position;
    Vec3f m_rotation;
    Vec3f m_scale;
    
    Matrix m_position_mtx;
    Matrix m_rotation_mtx;
    Matrix m_scale_mtx;
    Matrix m_local_mtx;

    void updateLocal();
};



} // namespace Folk


#endif // FOLK_SCENE__TRANSFORM_COMPONENT_HPP