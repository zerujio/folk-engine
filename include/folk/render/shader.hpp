#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"

#include <vector>

namespace Folk
{

/// \~spanish Resource que administra un programa de shaders de OpenGL. \~english A \ref Resource that manages an OpenGL shader program.
class Shader : public Resource
{
public:
    /// \~spanish Estructura para especificar los atributos (parámetros) del vertex shader. \~english Vertex attribute especification (for vertex shader).
    /**
     * \~spanish Al siguiente shader:
     * \~english For the following glsl attributes:
     * \~
     * ```glsl
     * layout (location = 0) in vec3 position;
     * layout (location = 1) in vec2 uv;
     * ```
     * \~spanish le corresponden los siguientes atributos:
     * \~english the following VertexAttrib should be used:
     * \~
     * ```cpp
     * VertexAttrib pos {0, 3 * sizeof(float), Type::Float, false, 5 * sizeof(float), 0};
     * VertexAttrib uv {1, 2 * sizeof(float), Type::Float, false, 5 * sizeof(float), 3 * sizeof(float)};
     * ```
    */
    struct VertexAttrib {
        enum class Type { Float, Int, Uint };

        /// \~spanish `location` en GLSL \~english glsl vertex attribute location.
        uint location;

        /// \~spanish Tamaño en bytes de cada atributo. \~english Size (in bytes) of each attribute.
        int size;

        /// \~spanish Tipo del atributo. \~english Attribute type.
        Type type;

        /// \~spanish ¿Debería normalizarse el valor del atributo?  \~english Should the attribute value be normalized?
        /**
         * \~spanish Rango de normalización: [-1, 1] para valores con signo, [0, 1] sin signo.
         * \~english Normalization range: [-1, 1] for signed types, [0, 1] for unsigned.
        */
        bool normalized;

        /// \~spanish _Stride_: separación (en bytes) entre elementos consecutivos. \~english Stride (separation between consecutive vertex attributes)
        int stride;

        /// \~spanish Distancia del inicio del buffer a la primera instancia del atributo. \~english Offset from the start of the vertex buffer.
        uint offset;
    };

    using VertexAttribArray = std::vector<VertexAttrib>;
    using Ref = Reference<Shader>;
    
    /// \~spanish Crea una instancia del shader predeterminado. \~english Create a default shader object.
    static Ref createDefaultShader();

    /// \~spanish Crea un programa a partir de código fuente GLSL. \~english Create a shader program from glsl source code.
    /**
     * \~spanish
     * \param vertex código fuente para el _vertex shader_.
     * \param fragment código fuente para el _fragment shader_.
     * \param attributes vector de VertexAttrib.
     * 
     * \~english
     * \param vertex source code for vertex shader.
     * \param fragment source code for fragment shader.
     * \param attributes vertex attribute vector.
     * 
     * \~
     * \see Shader::VertexAttrib
    */
    static Ref create(const char* vertex, const char* fragment, 
                      VertexAttribArray const& attributes);

    ~Shader();

private:
    VertexAttribArray vaa;

    Shader(const char*, const char*, VertexAttribArray const&);

    friend Ref;
    friend class Material;
    friend class Visual;
    friend class Renderer;
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_HPP