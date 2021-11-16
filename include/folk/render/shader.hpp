#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"

#include <bgfx/bgfx.h>

namespace Folk
{

/// \~spanish Un programa de shaders (vertex + fragment).
class Shader final : public Resource
{
public:
    using Ref = std::shared_ptr<Shader>;

    /// Crea una instancia del shader predeterminado.
    static Ref createDefault();

    /// Crea un programa a partir de archivos.
    /**
     * Ejemplo:
     * 
     * ```cpp
     * Shader::Ref shader = Shader::createFromFiles("vertex_shader.sc", "fragment_shader.sc");
     * ```
     * 
     * \param vertex Archivo que contiene el _vertex shader_.
     * \param fragment Archivo que contiene el _fragment shader_.
    */
    static Ref createFromFiles(const char* vertex, const char* fragment);

    Shader(const bgfx::ProgramHandle);
    ~Shader();

private:
    const bgfx::ProgramHandle handle;

    friend class Renderer;
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_HPP