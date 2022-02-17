#ifndef FOLK_RENDER__MATERIAL_HPP
#define FOLK_RENDER__MATERIAL_HPP

#include "folk/core/resource.hpp"
#include "folk/render/shader.hpp"

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

    /// Access the value of a uniform.
    class ConstUniform final {

        const Material& m_material;
        unsigned int m_uniform_index;

    public:

        ConstUniform(const Material& mat_, unsigned int index_)
        : m_material(mat_), m_uniform_index(index_)
        {
            if (m_uniform_index >= m_material.m_uniform_info.size())
                throw Error("Uniform index out of range");
        }

        /// Access the value of the uniform.
        template<UniformType T>
        [[nodiscard]] const UniformTypeRep<T>& value() const {
            if (T != m_material.m_shader->uniforms()[m_uniform_index].type)
                throw Error("Attempt to access uniform with incorrect type.");

            const auto data_index = m_material.m_uniform_info[m_uniform_index].data_index;
            return reinterpret_cast<const UniformTypeRep<T>&>(m_material.m_uniform_data[data_index]);
        }

        /// Access the Nth element of an array uniform.
        template<UniformType T>
        [[nodiscard]] const UniformTypeRep<T>& array(unsigned int n) const {
            if (n >= m_material.m_shader->uniforms()[m_uniform_index].count)
                throw Error("Uniform array index out of range.");

            auto ptr = &value<T>();

            return ptr[n];
        }

        /// Access the @p transposed property. This value is ignored for non matrix uniforms.
        [[nodiscard]] const bool& transposed() const {
            return m_material.m_uniform_info[m_uniform_index].transposed;
        }
    };

    /// Access the value of an uniform.
    class Uniform final {

        ConstUniform uniform;

    public:

        Uniform(Material& m, unsigned int i) : uniform(m, i) {}

        template<UniformType T>
        [[nodiscard]] UniformTypeRep<T>& value() const {
            return const_cast<UniformTypeRep<T>&>(uniform.template value<T>());
        }

        template<UniformType T>
        [[nodiscard]] UniformTypeRep<T>& array(unsigned int n) const {
            return const_cast<UniformTypeRep<T>&>(uniform.template array<T>(n));
        }

        [[nodiscard]] bool& transposed() const {
            return const_cast<bool&>(uniform.transposed());
        }
    };

    /// const access to the uniform at @p index
    [[nodiscard]] ConstUniform uniform(unsigned int index) const;

    /// Access to the uniform at @p index
    [[nodiscard]] Uniform uniform(unsigned int index);

    /// Find uniform by name
    [[nodiscard]] ConstUniform uniform(const std::string& name) const;
    [[nodiscard]] ConstUniform uniform(const char* name) const;
    [[nodiscard]] Uniform uniform(const std::string& name);
    [[nodiscard]] Uniform uniform(const char* name);

    /// find uniform index by name (-1 if not found).
    [[nodiscard]] int uniformIndex(const std::string& name) const;
    [[nodiscard]] int uniformIndex(const char *name) const;

private:

    using StorageUnit = GLuint;

    struct UniformInfo final {
        unsigned int data_index;    // index in the data buffer
        bool transposed;            // only for matrix types
    };

    std::shared_ptr<Shader> m_shader {};
    std::vector<UniformInfo> m_uniform_info {};
    std::vector<StorageUnit> m_uniform_data {};

    void addUniforms();
};

} // namespace folk


#endif//FOLK_RENDER__MATERIAL_HPP