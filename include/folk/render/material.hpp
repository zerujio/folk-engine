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
    
    static Ref createDefaultMaterial();
    static Ref create(Shader::Ref);

    void setShader(Shader::Ref);
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