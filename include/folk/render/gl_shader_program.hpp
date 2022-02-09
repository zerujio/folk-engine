#ifndef INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP
#define INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP

#include "gl_object.hpp"
#include "gl_shader.hpp"

namespace Folk::gl {

GLboolean _isProgram(GLuint id);

class ShaderProgramHandle : public BaseHandle<_isProgram> {
public:
    /// Link the GLSL program shaders. A shader must have been attached previously.
    void link() const;

    /// Attach a shader.
    void attach(ShaderHandle shader) const;

    /// Detach a shader.
    void detach(ShaderHandle shader) const;

    /// Make this shader program current.
    void use() const;
};

GLuint _createProgram();
void _deleteProgram(GLuint id);

using ShaderProgramManager = ObjectManager<ShaderProgramHandle, _createProgram, _deleteProgram>;

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP
