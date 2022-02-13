#ifndef INCLUDE_FOLK_RENDER__GL_SHADER_HPP
#define INCLUDE_FOLK_RENDER__GL_SHADER_HPP

#include "gl_object.hpp"

#include <string>
#include <type_traits>
#include <array>
#include <vector>

namespace Folk::gl {

enum class ShaderType {
    Vertex = GL_VERTEX_SHADER,
    TessCtrl = GL_TESS_CONTROL_SHADER,
    TessEval = GL_TESS_EVALUATION_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    Compute = GL_COMPUTE_SHADER
};

GLboolean _isShader(GLuint id);

class ShaderHandle : public BaseHandle<_isShader>{

    friend class ShaderProgram;

public:
    /**
     * @brief Set shader source code.
     * @param source_string A C string containing GLSL source code.
     */
    void setSource(const char* source_string) const;

    /**
     * @brief Set shader source code.
     * @param source_string A string containing GLSL source code.
     */
    void setSource(const std::string& source_string) const;


    /**
     * @brief Set shader source code.
     * @tparam N Size of the string array.
     * @param source_strings An array of std::string objects that will be concatenated together to form the source code.
     */
    template<auto N>
    void setSource(const std::array<std::string, N>& source_strings) const {
        const char* c_strings[N];
        for (int i = 0; i < N; ++i) {
            c_strings[i] = source_strings[i].c_str();
        }
        setSource(N, c_strings);
    }

    /**
     * @brief Set shader source code.
     * @param source_strings An array of std:string objects that will be concatenated together to form the source code.
     */
    void setSource(const std::vector<std::string>& source_strings) const;

    /**
     * @brief Set shader source code.
     * @tparam N Size of the string array.
     * @param source_strings An array of C strings that sill concatenated together to form the source code.
     */
    template<auto N>
    void setSource(const std::array<const char*, N>& source_strings) const {
        setSource(N, source_strings.data());
    }

    /**
     * @brief Set shader source code
     * @param source_strings A vector of C strings that will be concatenated together to form the source code.
     */
    void setSource(const std::vector<const char*>& source_strings) const;

    /**
     * @brief Set shader source code.
     * @tparam N length of the arrays
     * @param source_strings An array of non null-terminated character arrays strings that will be concatenated together
     * to form the source code.
     * @param lengths The lengths of the character arrays.
     */
    template<auto N>
    void setSource(const std::array<const char*, N>& source_strings, const std::array<GLint, N>& lengths) const {
        setSource(source_strings.data(), lengths.data());
    }

    /**
     * @brief Set shader source code
     * @param source_strings A vector of non null-terminated character arrays that will be concatenated together to form
     * the source code.
     * @param lengths The lengths of the character arrays.
     */
    void setSource(const std::vector<const char*>& source_strings, const std::vector<GLint>& lengths) const;

    /**
     * @brief Compile this shader. The shader source must have been previously set with setSource().
     */
    void compile() const;

private:
    // use multiple C strings as source code
    void setSource(int count, const char * const *strings) const;

    // use multiple non null-terminated character arrays as source code
    void setSource(int count, const char * const *strings, const GLint *lengths) const;
};

GLuint _createShader(ShaderType type);
void _deleteShader(GLuint id);

using ShaderManager = ObjectManager<ShaderHandle, _createShader, _deleteShader, ShaderType>;

} // namespace Folk::gl

#endif //INCLUDE_FOLK_RENDER__GL_SHADER_HPP
