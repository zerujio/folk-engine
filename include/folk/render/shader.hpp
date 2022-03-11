#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"
#include "gl_shader.hpp"
#include "gl_shader_program.hpp"
#include "vertex_attribute.hpp"
#include "uniform_type.hpp"
#include "vertex_types.hpp"

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
     * @brief Compile and link a shader program.
     * @param vert Source code for the vertex shader.
     * @param frag Source code for the fragment shader.
     */
    Shader(const std::string& vert, const std::string& frag);

    /**
     * @brief Compile and link a shader program from (null terminated) C strings.
     * @param vert Source code for the vertex shader.
     * @param frag Source code for the fragment shader.
     */
    Shader(const char* vert, const char* frag);

    /// Create a default shader for a built-in vertex type.
    template<class VertexType> static Ref createDefault();
    

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

    /// Type information for this shader program's uniforms.
    class UniformInfo final {

        friend class Renderer;
        friend class Material;

    public:
        /// Name of the uniform variable.
        std::string name;

        /// Data type of the uniform variable.
        UniformType type;

        /// Size of the variable. >1 for arrays.
        unsigned int count;

        /**
         * @brief Construct a new uniform specification.
         * @param name_ Name of the variable.
         * @param type_ Type of the uniform.
         * @param count_ Number of elements (>1 if its an array)
         * @param location_ (Internal usage) Uniform location or sampler texture unit.
         */
        UniformInfo(std::string name_, UniformType type_, unsigned int count_, unsigned int location_or_tex_unit_);

    private:
        unsigned int location_or_tex_unit;
    };

    /**
     * @brief Retrieve the list of user defined uniforms.
     * @return A vector containing uniform descriptors that can be used to modify the values of the uniforms.
     *
     * Note that "built-in" uniforms, such as u_ModelMatrix and u_ViewMatrix, will not show up in this list.
     */
    [[nodiscard]] const std::vector<UniformInfo>& uniforms() const { return m_uniforms; }

    /**
     * @brief The vertex attribute location that will be assigned by default to the given attribute names.
     *
     * Vertex shader variables defined with a name present in this list will be assigned the corresponding location.
     * Note that certain variable names are aliases for the same vertex attribute (like @p a_position and @p a_Position ).
     * When writing custom shaders, care should be taken not to define two variables with names mapped to the same location.
     *
     * Note that indices set using the `layout(location = i)` syntax take precedence over those specified here or in
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

    /// Identifies built in uniforms
    enum class BuiltInUniform : unsigned int {
        Model = 0,
        View,
        Projection
    };

    /// Lists the possible names for built-in uniforms
    static constexpr std::array builtin_uniform_names {
        std::pair("u_model", BuiltInUniform::Model),
        std::pair("u_Model", BuiltInUniform::Model),
        std::pair("u_view", BuiltInUniform::View),
        std::pair("u_View", BuiltInUniform::View),
        std::pair("u_proj", BuiltInUniform::Projection),
        std::pair("u_Proj", BuiltInUniform::Projection),
        std::pair("u_projection", BuiltInUniform::Projection),
        std::pair("u_Projection", BuiltInUniform::Projection),
    };

    /// Lists the type for each uniform.
    static constexpr std::array builtin_uniform_types {
        UniformType::fMat4, // Model
        UniformType::fMat4, // View
        UniformType::fMat4, // Projection
    };

    static constexpr UniformType getBuiltInUniformType(BuiltInUniform u) {
        return builtin_uniform_types[static_cast<unsigned int>(u)];
    }

private:
    gl::ShaderProgramManager m_shader_program {};
    std::vector<UniformInfo> m_uniforms {};     // uniform specification
    std::array<int, builtin_uniform_types.size()> m_builtin_uniform_locations {-1, -1, -1};
    GLuint m_texture_units {0}; // number of used texture units

    void compileAndLink(const char* vert_src, const char* frag_src);
    void parseUniforms();
    void addBuiltInUniform(const char* name, BuiltInUniform u_id, UniformType type, GLuint count, GLuint location);
    void addUserDefinedUniform(std::string name, UniformType type, GLuint count, GLuint location);

    [[nodiscard]] int& builtInUniformLoc(BuiltInUniform u);
    [[nodiscard]] const int& builtInUniformLoc(BuiltInUniform u) const;
};


template<> Shader::Ref Shader::createDefault<PositionVertex>();
template<> Shader::Ref Shader::createDefault<PositionNormalVertex>();
template<> Shader::Ref Shader::createDefault<PositionNormalTexCoordVertex>();

} // namespace Folk

#endif // FOLK_RENDER__SHADER_HPP