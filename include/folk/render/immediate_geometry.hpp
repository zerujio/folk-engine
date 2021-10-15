#ifndef FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP
#define FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP

#include "folk/render/common.hpp"

namespace Folk
{

/// A structure to specify geometry.
struct ImmediateGeometry
{   
    /// Vertices
    VertexArray vertices {};

    /// Element indices
    IndexArray indices {};

    /// Construct emtpy geometry.
    ImmediateGeometry() = default;

    /// Construct geometry with given vertices and indices.
    /**
     * @param v a vertex array.
     * @param i an index array.
    */
    ImmediateGeometry(VertexArray const& v, IndexArray const& i) 
        : vertices(v), indices(i) {}

    /// Construct triangle in XYZRGB format.
    static ImmediateGeometry rainbowTriangle();

    /// Construct triangle in XYZ format (no color).
    static ImmediateGeometry triangle();
};

} // namespace folk


#endif // FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP