//
// Created by sergio on 15-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__UNIFORM_TYPE_HPP
#define INCLUDE_FOLK_RENDER__UNIFORM_TYPE_HPP

#include "gl.hpp"
#include "folk/math.hpp"

namespace Folk {

/// All the possible uniform types
enum class UniformType : GLenum {

    Int     = GL_INT,
    UInt    = GL_UNSIGNED_INT,
    Float   = GL_FLOAT,

    Double  = GL_DOUBLE,

    fVec2               = GL_FLOAT_VEC2,
    fVec3               = GL_FLOAT_VEC3,
    fVec4               = GL_FLOAT_VEC4,
    iVec2               = GL_INT_VEC2,
    iVec3               = GL_INT_VEC3,
    iVec4               = GL_INT_VEC4,
    Bool                = GL_BOOL,
    bVec2               = GL_BOOL_VEC2,
    bVec3               = GL_BOOL_VEC3,
    bVec4               = GL_BOOL_VEC4,
    fMat2               = GL_FLOAT_MAT2,
    fMat3               = GL_FLOAT_MAT3,
    fMat4               = GL_FLOAT_MAT4,
    sampler1D           = GL_SAMPLER_1D,
    sampler2D           = GL_SAMPLER_2D,
    sampler3D           = GL_SAMPLER_3D,
    samplerCube         = GL_SAMPLER_CUBE,
    sampler1DShadow     = GL_SAMPLER_1D_SHADOW,
    sampler2DShadow     = GL_SAMPLER_2D_SHADOW,
    sampler2DRect       = GL_SAMPLER_2D_RECT,
    sampler2DRectShadow = GL_SAMPLER_2D_RECT_SHADOW,
    fMat2x3             = GL_FLOAT_MAT2x3,
    fMat2x4             = GL_FLOAT_MAT2x4,
    fMat3x2             = GL_FLOAT_MAT3x2,
    fMat3x4             = GL_FLOAT_MAT3x4,
    fMat4x2             = GL_FLOAT_MAT4x2,
    fMat4x3             = GL_FLOAT_MAT4x3,

    sampler1DArray          = GL_SAMPLER_1D_ARRAY,
    sampler2DArray          = GL_SAMPLER_2D_ARRAY,
    samplerBuffer           = GL_SAMPLER_BUFFER,
    sampler1DArrayShadow    = GL_SAMPLER_1D_ARRAY_SHADOW,
    sampler2DArrayShadow    = GL_SAMPLER_2D_ARRAY_SHADOW,
    samplerCubeShadow       = GL_SAMPLER_CUBE_SHADOW,
    uVec2                   = GL_UNSIGNED_INT_VEC2,
    uVec3                   = GL_UNSIGNED_INT_VEC3,
    uVec4                   = GL_UNSIGNED_INT_VEC4,
    isampler1D              = GL_INT_SAMPLER_1D,
    isampler2D              = GL_INT_SAMPLER_2D,
    isampler3D              = GL_INT_SAMPLER_3D,
    isamplerCube            = GL_INT_SAMPLER_CUBE,
    isampler2DRect          = GL_INT_SAMPLER_2D_RECT,
    isampler1DArray         = GL_INT_SAMPLER_1D_ARRAY,
    isampler2DArray         = GL_INT_SAMPLER_2D_ARRAY,
    isamplerBuffer          = GL_INT_SAMPLER_BUFFER,
    usampler1D              = GL_UNSIGNED_INT_SAMPLER_1D,
    usampler2D              = GL_UNSIGNED_INT_SAMPLER_2D,
    usampler3D              = GL_UNSIGNED_INT_SAMPLER_3D,
    usamplerCube            = GL_UNSIGNED_INT_SAMPLER_CUBE,
    usampler2DRect          = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
    usampler1DArray         = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
    usampler2DArray         = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
    usamplerBuffer          = GL_UNSIGNED_INT_SAMPLER_BUFFER,

    dMat2   = GL_DOUBLE_MAT2,
    dMat3   = GL_DOUBLE_MAT3,
    dMat4   = GL_DOUBLE_MAT4,
    dMat2x3 = GL_DOUBLE_MAT2x3,
    dMat2x4 = GL_DOUBLE_MAT2x4,
    dMat3x2 = GL_DOUBLE_MAT3x2,
    dMat3x4 = GL_DOUBLE_MAT3x4,
    dMat4x2 = GL_DOUBLE_MAT4x2,
    dMat4x3 = GL_DOUBLE_MAT4x3,

    dVec2   = GL_DOUBLE_VEC2,
    dVec3   = GL_DOUBLE_VEC3,
    dVec4   = GL_DOUBLE_VEC4,

    sampler2DMS         = GL_SAMPLER_2D_MULTISAMPLE,
    isampler2DMS        = GL_INT_SAMPLER_2D_MULTISAMPLE,
    usampler2DMS        = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
    sampler2DMSArray    = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
    isampler2DMSArray   = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
    usampler2DMSArray   = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
};

/// Check if a UniformType is a sampler.
bool isSampler(UniformType type);

namespace impl {

    template<UniformType T> struct TypeRep_struct;

#define FOLK_UNIFORM_TYPE_REP_DEF(ENUM, TYPE)\
template<> struct TypeRep_struct<UniformType::ENUM> { using type = TYPE; };

#define FOLK_UNIFORM_TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, SIZE) \
FOLK_UNIFORM_TYPE_REP_DEF(ENUM_PREFIX ## Vec ## SIZE, glm::TYPE_PREFIX ## vec ## SIZE)

#define FOLK_UNIFORM_TYPE_REP_DEF_VEC_ALL(ENUM_PREFIX, TYPE_PREFIX) \
FOLK_UNIFORM_TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, 2)       \
FOLK_UNIFORM_TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, 3)       \
FOLK_UNIFORM_TYPE_REP_DEF_VEC(ENUM_PREFIX, TYPE_PREFIX, 4)

#define FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, SIZE) \
FOLK_UNIFORM_TYPE_REP_DEF(ENUM_PREFIX ## Mat ## SIZE, glm::TYPE_PREFIX ## mat ## SIZE)

#define FOLK_UNIFORM_TYPE_REP_DEF_MAT_ALL(ENUM_PREFIX, TYPE_PREFIX) \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 2)       \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 3)       \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 4)       \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 2x3)     \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 2x4)     \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 3x2)     \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 3x4)     \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 4x2)     \
FOLK_UNIFORM_TYPE_REP_DEF_MAT(ENUM_PREFIX, TYPE_PREFIX, 4x3)


    // scalars
    FOLK_UNIFORM_TYPE_REP_DEF(Int, GLint)
    FOLK_UNIFORM_TYPE_REP_DEF(UInt, GLuint)
    FOLK_UNIFORM_TYPE_REP_DEF(Float, GLfloat)
    FOLK_UNIFORM_TYPE_REP_DEF(Double, GLdouble)
    FOLK_UNIFORM_TYPE_REP_DEF(Bool, bool)

    // vectors
    FOLK_UNIFORM_TYPE_REP_DEF_VEC_ALL(f,)
    FOLK_UNIFORM_TYPE_REP_DEF_VEC_ALL(i, i)
    FOLK_UNIFORM_TYPE_REP_DEF_VEC_ALL(b, b)
    FOLK_UNIFORM_TYPE_REP_DEF_VEC_ALL(u, u)
    FOLK_UNIFORM_TYPE_REP_DEF_VEC_ALL(d, d)

    // matrices
    FOLK_UNIFORM_TYPE_REP_DEF_MAT_ALL(f,)
    FOLK_UNIFORM_TYPE_REP_DEF_MAT_ALL(d, d)
};

/// The data type that represents each UniformType
template<UniformType T> using UTypeRep = typename impl::TypeRep_struct<T>::type;

/// Get uniform type as a C string.
const char* uniformTypeName(UniformType type_id);

std::ostream& operator<<(std::ostream& out, UniformType type_id);

}

#endif //INCLUDE_FOLK_RENDER__UNIFORM_TYPE_HPP
