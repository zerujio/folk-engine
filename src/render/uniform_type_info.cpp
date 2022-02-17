
#include "uniform_type_info.hpp"
#include "folk/error.hpp"

namespace Folk {

const UniformTypeInfo &UniformTypeInfo::get(UniformType type) {
    auto iter = s_info_map.find(type);

    if (iter == s_info_map.end())
        throw Error("Undefined type info!");

    return iter->second;
}

const UniformMatrixTypeInfo &UniformMatrixTypeInfo::get(UniformType type) {
    auto iter = s_info_map.find(type);

    if (iter == s_info_map.end())
        throw Error("Undefined type info!");

    return iter->second;
}

#define INFO(ENUM, glUniform) \
{UniformType::ENUM,           \
UniformTypeInfo{std::make_unique<glUniformFunctorImpl<UniformTypeBaseRep<UniformType::ENUM>>>(&(glUniform)), \
sizeof(UniformTypeRep<UniformType::ENUM>)}}

#define VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, N) INFO(ENUM_PREFIX ## Vec ## N, glUniform ## N ## UNIFORM_POSTFIX ## v)
#define VEC_INFO_ALL(ENUM_PREFIX, UNIFORM_POSTFIX) \
VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, 2), \
VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, 3), \
VEC_INFO(ENUM_PREFIX, UNIFORM_POSTFIX, 4)

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
};

#define INFO(ENUM, glUniform) \
{UniformType::ENUM,           \
UniformMatrixTypeInfo{std::make_unique<glUniformMatrixFunctorImpl<UniformTypeBaseRep<UniformType::ENUM>>>(&(glUniform)), \
sizeof(UniformTypeRep<UniformType::ENUM>)}}
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

const std::map<UniformType, UniformMatrixTypeInfo> UniformMatrixTypeInfo::s_info_map
{
        MAT_INFO_ALL(f, f),
        MAT_INFO_ALL(d, d)
};

} // namespace Fol