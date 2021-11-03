#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"

#include <vector>

namespace Folk
{

/// \~spanish Resource que administra un programa de shaders de OpenGL.
class Shader : public Resource
{
public:
    using Ref = Reference<Shader>;

    /// Construye un programa a partir de archivos de shaders precompilados.
    /**
     * \param vertex_file Nombre del archivo que contiene el _vertex shader_.
     * \param fragment_file Archivo que contiene el _fragment shader_.
    */
    static Ref createFromFiles(const char* vertex_file, const char* fragment_file);
    static Ref createDefault();

    ~Shader();

private:
    Shader();
    Shader(std::string const&, std::string const&);

    friend Ref;
    friend class Material;
    friend class Visual;
    friend class Renderer;
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_HPP