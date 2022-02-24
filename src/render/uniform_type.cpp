#include "folk/render/uniform_type.hpp"

#include "folk/render/texture.hpp"

namespace Folk {

const char *uniformTypeName(UniformType type_id) {

#define CASE(ENUM) case UniformType::ENUM: return #ENUM;

#define VEC_CASE(PREFIX, N) CASE(PREFIX ## Vec ## N)
#define ALL_VEC_CASES(PREFIX) \
VEC_CASE(PREFIX, 2)           \
VEC_CASE(PREFIX, 3)           \
VEC_CASE(PREFIX, 4)

#define MAT_CASE(PREFIX, DIM) CASE(PREFIX ## Mat ## DIM)
#define ALL_MAT_CASES(PREFIX) \
MAT_CASE(PREFIX, 2)           \
MAT_CASE(PREFIX, 3)           \
MAT_CASE(PREFIX, 4)           \
MAT_CASE(PREFIX, 2x3)         \
MAT_CASE(PREFIX, 2x4)         \
MAT_CASE(PREFIX, 3x2)         \
MAT_CASE(PREFIX, 3x4)         \
MAT_CASE(PREFIX, 4x2)         \
MAT_CASE(PREFIX, 4x3)


#define SAMPLER(ENUM) \
CASE(sampler ## ENUM) \
CASE(isampler ## ENUM)\
CASE(usampler ## ENUM)

    switch (type_id) {
        CASE(Float)
        ALL_VEC_CASES(f)
        ALL_MAT_CASES(f)

        CASE(Double)
        ALL_VEC_CASES(d)
        ALL_MAT_CASES(d)

        CASE(Int)
        ALL_VEC_CASES(i)

        CASE(UInt)
        ALL_VEC_CASES(u)

        CASE(Bool)
        ALL_VEC_CASES(b)

        SAMPLER(1D)
        SAMPLER(1DArray)
        CASE(sampler1DShadow)
        CASE(sampler1DArrayShadow)

        SAMPLER(Buffer)

        SAMPLER(2D)
        SAMPLER(2DArray)
        SAMPLER(2DMS)
        SAMPLER(2DMSArray)
        SAMPLER(2DRect)
        CASE(sampler2DShadow)
        CASE(sampler2DArrayShadow)
        CASE(sampler2DRectShadow)

        SAMPLER(3D)

        SAMPLER(Cube)
        CASE(samplerCubeShadow)

        default:
            return "<unknown type>";
    }
}

std::ostream &operator<<(std::ostream &out, UniformType type_id) {
    out << uniformTypeName(type_id);
    return out;
}

bool isSampler(UniformType type) {
    return (type >= UniformType::sampler1D && type <= UniformType::sampler2DRectShadow)
        || (type >= UniformType::sampler1DArray && type <= UniformType::samplerCubeShadow)
        || (type >= UniformType::isampler1D && type <= UniformType::usamplerBuffer)
        || (type >= UniformType::sampler2DMS && type <= UniformType::usampler2DMSArray);
}

} // namespace Folk