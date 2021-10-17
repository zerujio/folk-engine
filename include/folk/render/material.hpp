#ifndef FOLK_RENDER__MATERIAL_HPP
#define FOLK_RENDER__MATERIAL_HPP

#include "folk/core/resource.hpp"
#include "folk/render/shader.hpp"

namespace Folk
{

/// \~ Determina la forma en que una malla es dibujada. \~english Determines the way a Mesh is rendered.
/**
 * \~spanish
 * Un Material agrupa texturas, shaders y sus argumentos.
 * 
 * \~english
 * A material groups shaders, textures, and other shader parameters.
*/
class Material : public Resource {

public:
    using Ref = Reference<Material>;
    
    /// \~spanish Crea un material con el shader predeterminado. \~english Create a material with default shader.
    static Ref createDefaultMaterial();

    /// \~spanish Crea un material con el Shader dado. \~english Create material with given shader.
    /**
     * \~spanish
     * \param shader Referencia a un Shader.
     * 
     * \~english
     * \param shader A reference to a \ref Shader resource.
    */
    static Ref create(Shader::Ref shader);

    /// \~spanish Cambia el Shader. \~english Change the shader.
    /**
     * \~spanish
     * \param shader Referencia a un Shader.
     * 
     * \~english
     * \param shader Reference to Shader resource.
    */
    void setShader(Shader::Ref shader);

    /// \~spanish Obtiene el Shader de este material. \~english Get shader.
    /**
     * \~spanish 
     * \return una referencia al shader en uso.
     * 
     * \~english
     * \return The \ref Shader currently in use.
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