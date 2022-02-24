//
// Created by sergio on 24-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_UNIFORM_HPP
#define INCLUDE_FOLK_RENDER__GL_UNIFORM_HPP

#include "gl.hpp"

#include <vector>

namespace Folk::gl {

template<typename T>
using glUniform_t = void (*) (GLint, GLsizei, const T*);

template<class FunctionType> class FuncRef;

template<class... Args>
class FuncRef<void (*)(Args...)> {
public:
    using FunctionType = void (*)(Args...);

    FuncRef(const FunctionType& function) noexcept : m_function_ptr(function) {}

    void operator() (Args... args) const {
        gl::call::fast(m_function_ptr)(args...);
    }

private:
    const FunctionType & m_function_ptr;
};

template<typename T> struct uniformSetters;

template<>
struct uniformSetters<GLfloat> {
    static const FuncRef<glUniform_t<GLfloat>> array[4];
};

template<>
struct uniformSetters<GLdouble> {
    static const FuncRef<glUniform_t<GLdouble>> array[4];
};

template<>
struct uniformSetters<GLint> {
    static const FuncRef<glUniform_t<GLint>> array[4];
};

template<>
struct uniformSetters<GLuint> {
    static const FuncRef<glUniform_t<GLuint>> array[4];
};

/**
 * @brief Wraps @p glUniform{1|2|3|4}{f|d|i|ui}v functions.
 * @tparam T The data type.
 * @param location Uniform location.
 * @param value_count Number of values. >1 indicates an array.
 * @param type_length Number of elements per value (e.g. 4 for a vec4).
 * @param values A pointer to the value(s) to set.
 */
template<typename T>
void setUniform(GLint location, uint type_length, GLsizei value_count, const T* values) {
    uniformSetters<T>::array[type_length - 1](location, value_count, values);
}

/// bool specialization
template<> void setUniform<bool>(GLint location, uint type_length, GLsizei value_count, const bool* values);

// matrices

template<typename T>
using glUniformMatrix_t = void (*) (GLint, GLsizei, GLboolean, const T*);

template<typename> struct uniformMatrixSetters;

template<>
struct uniformMatrixSetters<GLfloat> {
    static const FuncRef<glUniformMatrix_t<GLfloat>> array[3][3];
};

template<>
struct uniformMatrixSetters<GLdouble> {
    static const FuncRef<glUniformMatrix_t<GLdouble>> array[3][3];
};

/**
 * @brief Set a matrix uniform.
 * @tparam T The basic data type. Either GLfloat or GLdouble.
 * @param location Uniform location.
 * @param rows Rows of the matrix type.
 * @param columns Columns of the matrix type.
 * @param count Number of matrices (>1 for arrays).
 * @param values pointer to data.
 *
 * Passing rows=2 and columns=3 with T=GLfloat will call glUniformMatrix2x3fv(...)
 */
template<typename T>
void setUniformMatrix(GLint location, uint rows, uint columns, GLsizei count, GLboolean transposed, const T* values) {
    uniformMatrixSetters<T>::array[rows - 2][columns - 2](location, count, transposed, values);
}

} // namespace Folk::gl

#endif //INCLUDE_FOLK_RENDER__GL_UNIFORM_HPP

