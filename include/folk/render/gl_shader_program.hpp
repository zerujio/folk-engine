#ifndef INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP
#define INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP

#include "gl_object.hpp"
#include "gl_shader.hpp"

namespace Folk::gl {

GLboolean _isProgram(GLuint id);

class ShaderProgram : public BaseHandle<_isProgram> {
public:
    /// Link the GLSL program shaders. A shader must have been attached previously.
    void link() const;

    /// Attach a shader.
    void attach(ShaderHandle shader) const;

    /// Detach a shader.
    void detach(ShaderHandle shader) const;

    /// Make this shader program current.
    void bind() const;

    /// Unbind the currently bound shader program.
    static void unbind();

    /// Bind a variable name to a vertex attribute index. Must be called before linking for it to take effect.
    void bindAttribLocation(GLuint index, const char* name) const;
};

GLuint _createProgram();
void _deleteProgram(GLuint id);

using ShaderProgramManager = ObjectManager<ShaderProgram, _createProgram, _deleteProgram>;

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP
