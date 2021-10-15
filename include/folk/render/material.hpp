#ifndef FOLK_RENDER__MATERIAL_HPP
#define FOLK_RENDER__MATERIAL_HPP

#include "folk/core/resource.hpp"
#include "folk/render/shader.hpp"

namespace Folk
{

/// Determines the way a Mesh is rendered.
/**
 * A material groups shaders, textures, and other shader parameters.
*/
class Material : public Resource {

public:
    using Ref = Reference<Material>;
    
    /// Create a material with default shader.
    static Ref createDefaultMaterial();

    /// Create material with given shader.
    /**
     * @param shader A reference to a @ref Shader resource.
    */
    static Ref create(Shader::Ref shader);

    /// Change the shader.
    /**
     * @param shader reference to Shader resource.
    */
    void setShader(Shader::Ref shader);

    /// Get shader.
    /**
     * @return The @ref Shader currently in use.
    */
    Shader::Ref getShader();

    ~Material();

private:
    Shader::Ref shader;
    Material(Shader::Ref);

    friend class Visual;
    friend class RenderModule;
};

} // namespace folk


#endif//FOLK_RENDER__MATERIAL_HPP