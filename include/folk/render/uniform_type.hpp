//
// Created by sergio on 15-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__UNIFORM_TYPE_HPP
#define INCLUDE_FOLK_RENDER__UNIFORM_TYPE_HPP

#include "gl.hpp"
#include "folk/math.hpp"

namespace Folk {

enum class UniformType : GLenum {

    // float
    Float = GL_FLOAT,

    fVec2 = GL_FLOAT_VEC2,
    fVec3 = GL_FLOAT_VEC3,
    fVec4 = GL_FLOAT_VEC4,

    fMat2 = GL_FLOAT_MAT2,
    fMat3 = GL_FLOAT_MAT3,
    fMat4 = GL_FLOAT_MAT4,

    fMat2x3 = GL_FLOAT_MAT2x3,
    fMat2x4 = GL_FLOAT_MAT2x4,

    fMat3x2 = GL_FLOAT_MAT3x2,
    fMat3x4 = GL_FLOAT_MAT3x4,

    fMat4x2 = GL_FLOAT_MAT4x2,
    fMat4x3 = GL_FLOAT_MAT4x3,

    // int
    Int = GL_INT,

    iVec2 = GL_INT_VEC2,
    iVec3 = GL_INT_VEC3,
    iVec4 = GL_INT_VEC4,

    // uint
    UInt = GL_UNSIGNED_INT,
    uVec2 = GL_UNSIGNED_INT_VEC2,
    uVec3 = GL_UNSIGNED_INT_VEC3,
    uVec4 = GL_UNSIGNED_INT_VEC4,

    // double
    Double = GL_DOUBLE,

    dVec2 = GL_DOUBLE_VEC2,
    dVec3 = GL_DOUBLE_VEC3,
    dVec4 = GL_DOUBLE_VEC4,

    dMat2 = GL_DOUBLE_MAT2,
    dMat3 = GL_DOUBLE_MAT3,
    dMat4 = GL_DOUBLE_MAT4,

    dMat2x3 = GL_DOUBLE_MAT2x3,
    dMat2x4 = GL_DOUBLE_MAT2x4,

    dMat3x2 = GL_DOUBLE_MAT3x2,
    dMat3x4 = GL_DOUBLE_MAT3x4,

    dMat4x2 = GL_DOUBLE_MAT4x2,
    dMat4x3 = GL_DOUBLE_MAT4x3,

    // bool
    Bool = GL_BOOL,

    bVec2 = GL_BOOL_VEC2,
    bVec3 = GL_BOOL_VEC3,
    bVec4 = GL_BOOL_VEC4,

    // texture samplers
    sampler1D = GL_SAMPLER_1D,
    sampler2D = GL_SAMPLER_2D,
};

namespace impl {

template<UniformType T> struct TypeRep_struct;

#define TYPE_REP_DEF(ENUM, TYPE)\
template<> struct TypeRep_struct<UniformType::ENUM> { using type = TYPE; };

// scalars
TYPE_REP_DEF(Int, GLint)
TYPE_REP_DEF(UInt, GLuint)
TYPE_REP_DEF(Float, GLfloat)
TYPE_REP_DEF(Double, GLdouble)
TYPE_REP_DEF(Bool, GLint)


#define TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, SIZE)\
TYPE_REP_DEF(ENUM_PREFIX ## Vec ## SIZE, glm::TYPE_PREFIX ## vec ## SIZE)

#define TYPE_REP_DEF_VEC_ALL(ENUM_PREFIX, TYPE_PREFIX) \
TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, 2)       \
TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, 3)       \
TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, 4)

// vectors
TYPE_REP_DEF_VEC_ALL(f, )
TYPE_REP_DEF_VEC_ALL(i, i)
TYPE_REP_DEF_VEC_ALL(b, b)
TYPE_REP_DEF_VEC_ALL(u, u)
TYPE_REP_DEF_VEC_ALL(d, d)


#define TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, SIZE) \
TYPE_REP_DEF(ENUM_PREFIX ## Mat ## SIZE, glm::TYPE_PREFIX ## mat ## SIZE)

#define TYPE_REP_DEF_MAT_ALL(ENUM_PREFIX, TYPE_PREFIX) \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 2)       \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 3)       \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 4)       \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 2x3)     \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 2x4)     \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 3x2)     \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 3x4)     \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 4x2)     \
TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 4x3)

// matrices
TYPE_REP_DEF_MAT_ALL(f, )
TYPE_REP_DEF_MAT_ALL(d, d)
}

/// Type used to represent each uniform type
template<UniformType T> using UniformTypeRep = typename impl::TypeRep_struct<T>::type;

namespace impl {
    template<typename T> struct BaseType_struct { using type = T; };

    template<auto L, typename T, auto Q>
    struct BaseType_struct<glm::vec<L, T, Q>> { using type = T; };

    template<auto C, auto R, typename T, auto Q>
    struct BaseType_struct<glm::mat<C, R, T, Q>> { using type = T; };
};

/// Base type of the representation (e.g. float for glm::vec3).
template<UniformType T> using UniformTypeBaseRep = typename impl::BaseType_struct<UniformTypeRep<T>>::type;

struct UniformTypeInfo;

}

#endif //INCLUDE_FOLK_RENDER__UNIFORM_TYPE_HPP
