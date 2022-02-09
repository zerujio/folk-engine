#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"
#include "gl_shader.hpp"
#include "gl_shader_program.hpp"

namespace Folk
{

/// A shader program.
class Shader final : public Resource
{
    friend class Renderer;

public:
    using Ref = std::shared_ptr<Shader>;

    /**
     * @brief Create a shader from glsl source code
     * @tparam StringContainerV A string container type (e.g. std::vector<std::string>, std::array<const char*>, etc.)
     * @tparam StringContainerF A string container type
     * @param vertex_source Source code for the vertex shader.
     * @param fragment_source Source code for the fragment shader.
     */
    template<class StringContainerV, class StringContainerF>
    Shader(const StringContainerV& vertex_source, const StringContainerF& fragment_source) {
        gl::ShaderManager vert {gl::ShaderType::Vertex};
        vert.setSource(vertex_source);
        vert.compile();

        gl::ShaderManager frag {gl::ShaderType::Fragment};
        frag.setSource(fragment_source);
        frag.compile();

        linkProgram(vert, frag);
    }

    Shader(const std::string& vert, const std::string& frag);
    Shader(const char* vert, const char* frag);

    /// Crea una instancia del shader predeterminado.
    static Ref createDefault();

    /// Crea un programa a partir de archivos.
    /**
     * Ejemplo:
     * 
     * ```cpp
     * Shader::Ref shader = Shader::createFromFiles("shader.vert", "shader.frag");
     * ```
     * 
     * \param vertex Archivo que contiene el vertex shader.
     * \param fragment Archivo que contiene el fragment shader.
    */
    static Ref createFromFiles(const char* vertex, const char* fragment);

private:
    void compileShadersAndLinkProgram(const char *vert, const char *frag) const;
    void linkProgram(gl::ShaderHandle vert, gl::ShaderHandle frag) const;

    gl::ShaderProgramManager m_shader_program {};
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_HPP