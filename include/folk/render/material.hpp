#ifndef FOLK_RENDER__MATERIAL_HPP
#define FOLK_RENDER__MATERIAL_HPP

#include "folk/core/resource.hpp"
#include "shader.hpp"
#include "uniform.hpp"

#include <vector>
#include <memory>

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

    friend class Renderer;

public: 
    /// Crea un material con el shader predeterminado.
    static std::shared_ptr<Material> create();

    /// Crea un material con el shader provisto.
    static std::shared_ptr<Material> create(std::shared_ptr<Shader> shader);

    explicit Material(std::shared_ptr<Shader> shader_);

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
    [[nodiscard]] std::shared_ptr<Shader> getShader() const;

    /**
     * @brief Access a uniform by index.
     * @tparam uType The expected type of the uniform. Must correspond to the one declared in the GLSL shader.
     * @param index The index of the uniform in the Shader's uniform list.
     * @return A reference to the uniform at @p index.
     */
    template<UniformType uType>
    [[nodiscard]] const Uniform<UTypeRep<uType>>& uniform(unsigned int index) const {
        if (index >= m_uniforms.size())
            throw Error("Uniform list access out of range");

        auto* derived_ptr = dynamic_cast<const Uniform<UTypeRep<uType>>*>(m_uniforms[index].get());

        if (!derived_ptr) {
            // dynamic cast failed because the uniform is not of the requested type.
            const auto &info {m_shader->uniforms()[index]};
            std::stringstream msg {"Uniform "};
            msg << info.name << " of type " << info.type << " accessed as " << uType << ".";
            throw Error(msg.str());
        }

        return *derived_ptr;
    }

    template<UniformType utype>
    [[nodiscard]] auto& uniform(unsigned int index) {
        const auto const_this = this;
        return const_cast<Uniform<UTypeRep<utype>>&>(const_this->uniform<utype>(index));
    }

    /**
     * @brief Access uniform by name.
     * @tparam uType The type of the uniform declared in the GLSL shader.
     * @param name The name of the variable in the GLSL shader.
     * @return A reference to the corresponding Uniform object.
     */
    template<UniformType uType>
    [[nodiscard]] const auto& uniform(const char* name) const {
        int index = uniformIndex(name);

        if (index < 0) {
            std::string msg {"No uniform named "};
            msg += name;
            throw Error(msg);
        }

        return uniform<uType>(index);
    }

    template<UniformType uType>
    [[nodiscard]] const auto& uniform(const std::string& name) const {
        return uniform<uType>(name.c_str());
    }

    template<UniformType uType>
    [[nodiscard]] auto& uniform(const char* name) {
        const Material* const_this = this;
        return const_cast<Uniform<UTypeRep<uType>>&>(const_this->uniform<uType>(name));
    }

    template<UniformType uType>
    [[nodiscard]] auto& uniform(const std::string& name) {
        return uniform<uType>(name.c_str());
    }

    /**
     * @brief Search for the index of the uniform with a given name.
     * @param name The name of the uniform variable (in the GLSL shader).
     * @return The index of the uniform named @p name, or -1 if no such uniform exists.
     */
    [[nodiscard]] int uniformIndex(const std::string& name) const;
    [[nodiscard]] int uniformIndex(const char *name) const;

    /// The amount of uniforms in this Material.
    [[nodiscard]] unsigned int uniformCount() const;

private:

    std::shared_ptr<Shader> m_shader {};
    std::vector<std::unique_ptr<IUniform>> m_uniforms {};

    // Add the uniforms listed in m_shader.uniforms() to m_uniforms.
    void addUniforms();

    // create a Uniform object based on a uniform declaration
    static std::unique_ptr<IUniform> parseUniform(const Shader::UniformInfo& uniform_decl);
};

} // namespace folk


#endif//FOLK_RENDER__MATERIAL_HPP