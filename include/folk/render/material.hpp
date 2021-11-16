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
    /// Crea un material con el shader predeterminado.
    static std::shared_ptr<Material> create();

    /// Crea un material con el shader provisto.
    static std::shared_ptr<Material> create(std::shared_ptr<Shader> shader);

    /// \~spanish Cambia el Shader. \~english Change the shader.
    /**
     * \~spanish
     * \param shader Referencia a un Shader.
     * 
     * \~english
     * \param shader Reference to Shader resource.
    */
    void setShader(std::shared_ptr<Shader> shader);

    /// \~spanish Obtiene el Shader de este material. \~english Get shader.
    /**
     * \~spanish 
     * \return una referencia al shader en uso.
     * 
     * \~english
     * \return The \ref Shader currently in use.
    */
    std::shared_ptr<Shader> getShader();

    Material(std::shared_ptr<Shader> shader_) : shader(shader_) {}

private:
    std::shared_ptr<Shader> shader;
};

} // namespace folk


#endif//FOLK_RENDER__MATERIAL_HPP