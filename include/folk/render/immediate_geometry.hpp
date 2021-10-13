#ifndef FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP
#define FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP

#include "folk/render/common.hpp"

namespace Folk
{

struct ImmediateGeometry
{
    VertexArray vertices {};
    IndexArray indices {};
    std::size_t const stride = 6;

    ImmediateGeometry() = default;

    ImmediateGeometry(VertexArray const& v, IndexArray const& i) 
        : vertices(v), indices(i) {}

    static ImmediateGeometry rainbowTriangle();
    static ImmediateGeometry triangle();
};

} // namespace folk


#endif // FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP