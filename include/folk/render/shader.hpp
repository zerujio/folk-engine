#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"

#include <vector>

namespace Folk
{

/// A @ref Resource that manages an OpenGL shader program.
class Shader : public Resource
{
public:
    /// Vertex attribute especification (for vertex shader).
    /**
     * For the following glsl attributes:
     * ```glsl
     * layout (location = 0) in vec3 position;
     * layout (location = 1) in vec2 uv;
     * ```
     * the following VertexAttrib should be used:
     * ```cpp
     * VertexAttrib pos {0, 3 * sizeof(float), Type::Float, false, 5 * sizeof(float), 0};
     * VertexAttrib uv {1, 2 * sizeof(float), Type::Float, false, 5 * sizeof(float), 3 * sizeof(float)};
     * ```
    */
    struct VertexAttrib {
        enum class Type { Float, Int, Uint };

        /// glsl vertex attribute location.
        uint location;

        /// Size (in bytes) of each attribute.
        int size;

        /// Attribute type.
        Type type;

        /// ¿Should the attribute value be normalized?
        /**
         * Normalization range: [-1, 1] for signed types, [0, 1] for unsigned.
        */
        bool normalized;

        /// Stride (separation between consecutive vertex attributes)
        int stride;

        /// Offset from the start of the vertex buffer.
        uint offset;
    };

    using VertexAttribArray = std::vector<VertexAttrib>;
    using Ref = Reference<Shader>;
    
    /// Create a default shader object.
    static Ref createDefaultShader();

    /// Create a shader program from glsl source code.
    /**
     * @param vertex source code for vertex shader.
     * @param fragment source code for fragment shader.
     * @param attributes vertex attribute vector.
     * 
     * @see Shader::VertexAttrib
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
    friend class RenderModule;
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_HPP