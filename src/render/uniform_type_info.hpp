//
// Created by sergio on 15-02-22.
//

#ifndef SRC_RENDER__UNIFORM_TYPE_INFO_HPP
#define SRC_RENDER__UNIFORM_TYPE_INFO_HPP

#include "folk/render/uniform_type.hpp"

#include <functional>
#include <map>

namespace Folk {

// This is necessary to set the uniform without knowing its type
struct glUniformFunctor {
    virtual ~glUniformFunctor() = 0;
    virtual void operator() (unsigned int location, unsigned int count, const void* value) const = 0;
};

struct UniformTypeInfo final {

    std::unique_ptr<glUniformFunctor> p_glUniform;
    unsigned int size;  // size in bytes of the type

    static const UniformTypeInfo& get(UniformType type);

private:
    static const std::map<UniformType, UniformTypeInfo> s_info_map;
};

template<class ValueType>
class glUniformFunctorImpl final : public glUniformFunctor {

    void (**glUniform) (GLint, GLsizei, const ValueType*);

public:
    glUniformFunctorImpl(decltype(glUniform) function) : glUniform(function) {}

    ~glUniformFunctorImpl() override = default;

    void operator() (unsigned int location, unsigned int count, const void* value) const override {
        (*glUniform)(static_cast<GLint>(location), static_cast<GLsizei>(count),
                reinterpret_cast<const ValueType*>(value));
    }
};

// same for matrix uniform types

struct glUniformMatrixFunctor {
    virtual ~glUniformMatrixFunctor() = 0;
    virtual void operator() (unsigned int loc, unsigned int count, bool transpose, const void* value) const = 0;
};

struct UniformMatrixTypeInfo final {

    std::unique_ptr<glUniformMatrixFunctor> glUniformMatrix;
    unsigned int size;

    static const UniformMatrixTypeInfo& get(UniformType type);

    static constexpr bool is(UniformType type) {
        return (type >= UniformType::fMat2 && type <= UniformType::fMat4x3)
               || (type >= UniformType::dMat2 && type <= UniformType::dMat4x3);
    }

private:
    static const std::map<UniformType, UniformMatrixTypeInfo> s_info_map;
};

template<class ValueType>
class glUniformMatrixFunctorImpl final : public glUniformMatrixFunctor {

    void (**glUniform) (GLint, GLsizei, GLboolean, const ValueType*);

public:
    glUniformMatrixFunctorImpl(decltype(glUniform) u) : glUniform(u) {}
    ~glUniformMatrixFunctorImpl() override = default;

    void operator() (unsigned int loc, unsigned int count, bool transpose, const void* value) const override {
        (*glUniform)(static_cast<GLint>(loc), static_cast<GLsizei>(count),
                transpose, reinterpret_cast<const ValueType*>(value));
    }

};

} // namespace Folk

#endif //SRC_RENDER__UNIFORM_TYPE_INFO_HPP
