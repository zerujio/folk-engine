#include "folk/render/gl_uniform.hpp"

namespace Folk::gl {

const FuncRef<glUniform_t<GLfloat>> uniformSetters<GLfloat>::array[4] {
        glUniform1fv, glUniform2fv, glUniform3fv, glUniform4fv
};

const FuncRef<glUniform_t<GLdouble>> uniformSetters<GLdouble>::array[4] {
        glUniform1dv, glUniform2dv, glUniform3dv, glUniform4dv
};

const FuncRef<glUniform_t<GLint>> uniformSetters<GLint>::array[4] {
        glUniform1iv, glUniform2iv, glUniform3iv, glUniform4iv
};

const FuncRef<glUniform_t<GLuint>> uniformSetters<GLuint>::array[4] {
        glUniform1uiv, glUniform2uiv, glUniform3uiv, glUniform4uiv
};

template<>
void setUniform<bool>(GLint location, uint type_length, GLsizei value_count, const bool* values) {
    std::vector<GLint> expanded_values (value_count * type_length);

    for (int i = 0; i < expanded_values.size(); ++i)
        expanded_values[i] = values[i];

    uniformSetters<GLint>::array[type_length - 1](location, value_count, expanded_values.data());
}


const FuncRef<glUniformMatrix_t<GLfloat>> uniformMatrixSetters<GLfloat>::array[3][3] {
        {glUniformMatrix2fv, glUniformMatrix2x3fv, glUniformMatrix2x4fv},
        {glUniformMatrix3x2fv, glUniformMatrix3fv, glUniformMatrix3x4fv},
        {glUniformMatrix4x2fv, glUniformMatrix4x3fv, glUniformMatrix4fv}
};

const FuncRef<glUniformMatrix_t<GLdouble>> uniformMatrixSetters<GLdouble>::array[3][3] {
        {glUniformMatrix2dv, glUniformMatrix2x3dv, glUniformMatrix2x4dv},
        {glUniformMatrix3x2dv, glUniformMatrix3dv, glUniformMatrix3x4dv},
        {glUniformMatrix4x2dv, glUniformMatrix4x3dv, glUniformMatrix4dv}
};

} // namespace Folk::gl