
#include "uniform_type_info.hpp"
#include "folk/error.hpp"

namespace Folk {

template<class ValueType, bool isMatrix> class glUniformFunctorImpl;

template<class ValueType>
class glUniformFunctorImpl<ValueType, false> final : public glUniformFunctor {

public:
    using glUniformT = void (*) (GLint, GLsizei, const ValueType*);

    glUniformFunctorImpl(const glUniformT& function) : glUniform(function) {}

    ~glUniformFunctorImpl() override = default;

    void operator() (unsigned int location, unsigned int count, const void* value, bool transposed) const override {
        gl::call::fast(glUniform)(
                static_cast<GLint>(location),
                static_cast<GLsizei>(count),
                reinterpret_cast<const ValueType*>(value));
    }

private:
    const glUniformT& glUniform;
};

template<class ValueType>
class glUniformFunctorImpl<ValueType, true> final : public glUniformFunctor {

public:
    using glUniformT = void (*) (GLint, GLsizei, GLboolean transposed, const ValueType*);

    glUniformFunctorImpl(const glUniformT& function) : glUniform(function) {}

    ~glUniformFunctorImpl() override = default;

    void operator() (unsigned int loc, unsigned int count, const void* value, bool transposed) const override {
        gl::call::fast(glUniform)(
                static_cast<GLint>(loc),
                static_cast<GLsizei>(count),
                static_cast<GLboolean>(transposed),
                reinterpret_cast<const ValueType*>(value));
    }

private:
    const glUniformT& glUniform;
};

const UniformTypeInfo &UniformTypeInfo::get(UniformType type) {
    auto iter = s_info_map.find(type);

    if (iter == s_info_map.end())
        throw Error("Undefined type info!");

    return iter->second;
}


template<UniformType T, class Functor = glUniformFunctorImpl<UniformTypeBaseRep<T>, UniformTypeInfo::isMatrix(T)>>
UniformTypeInfo makeInfo( const typename Functor::glUniformT & gl_uniform, std::size_t size) {
    return {size, std::make_shared<Functor>(gl_uniform)};
}

#define INFO(ENUM, glUniform) \
std::pair(UniformType::ENUM, makeInfo<UniformType::ENUM>(glUniform, sizeof(UniformTypeRep<UniformType::ENUM>)))

#define VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, N) INFO(ENUM_PREFIX ## Vec ## N, glUniform ## N ## UNIFORM_POSTFIX ## v)
#define VEC_INFO_ALL(ENUM_PREFIX, UNIFORM_POSTFIX) \
VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, 2), \
VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, 3), \
VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, 4)

#define MAT_INFO(PREFIX, POSTFIX, DIM) INFO(PREFIX ## Mat ## DIM, glUniformMatrix ## DIM ## POSTFIX ## v)
#define MAT_INFO_ALL(PREFIX, POSTFIX) \
MAT_INFO(PREFIX, POSTFIX, 2), \
MAT_INFO(PREFIX, POSTFIX, 3), \
MAT_INFO(PREFIX, POSTFIX, 4), \
MAT_INFO(PREFIX, POSTFIX, 2x3),       \
MAT_INFO(PREFIX, POSTFIX, 2x4),       \
MAT_INFO(PREFIX, POSTFIX, 3x2),       \
MAT_INFO(PREFIX, POSTFIX, 3x4),       \
MAT_INFO(PREFIX, POSTFIX, 4x2),       \
MAT_INFO(PREFIX, POSTFIX, 4x3)


const std::map<UniformType, UniformTypeInfo> UniformTypeInfo::s_info_map
{
        INFO(Int, glUniform1iv),
        VEC_INFO_ALL(i, i),

        INFO(UInt, glUniform1uiv),
        VEC_INFO_ALL(u, ui),

        INFO(Float, glUniform1fv),
        VEC_INFO_ALL(f, f),

        INFO(Double, glUniform1dv),
        VEC_INFO_ALL(d, d),

        MAT_INFO_ALL(f, f),
        MAT_INFO_ALL(d, d)
};
} // namespace Fol