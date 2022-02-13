#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"
#include "gl_shader.hpp"
#include "gl_shader_program.hpp"
#include "vertex_attribute.hpp"

#include <array>
#include <vector>
#include <tuple>

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

    /**
     * @brief The vertex attribute index that will be assigned by default to the given attribute names.
     *
     * Vertex shader variables defined with a name present in this list will be assigned the corresponding index.
     * Note that certain variable names are aliases for the same vertex attribute (like @p a_position and @p a_Position).
     * When writing custom shaders, care should be taken not to define two variables with names mapped to the same index.
     *
     * Note that indices set using the `layout(location = index)` syntax take precedence over those specified here or in
     * @p user_attribute_indices.
     */
    static constexpr std::array builtin_attribute_indices {
        std::pair("a_position", DefaultAttribIndex::Position),
        std::pair("a_Position", DefaultAttribIndex::Position),
        std::pair("a_normal", DefaultAttribIndex::Normal),
        std::pair("a_Normal", DefaultAttribIndex::Normal),
        std::pair("a_tex_coord", DefaultAttribIndex::TexCoord),
        std::pair("a_texCoord", DefaultAttribIndex::TexCoord),
        std::pair("a_TexCoord", DefaultAttribIndex::TexCoord),
        std::pair("a_color", DefaultAttribIndex::Color),
        std::pair("a_Color", DefaultAttribIndex::Color)
    };

    /// Same as @p builtin_attribute_indices , but specified by the user.
    static std::vector<std::pair<const char*, GLuint>> user_attribute_indices;

private:
    void compileShadersAndLinkProgram(const char *vert, const char *frag) const;
    void linkProgram(gl::ShaderHandle vert, gl::ShaderHandle frag) const;

    gl::ShaderProgramManager m_shader_program {};
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_HPP