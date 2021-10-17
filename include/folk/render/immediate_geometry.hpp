#ifndef FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP
#define FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP

#include "folk/render/common.hpp"

namespace Folk
{

/// \brief \~spanish Una estructura para especificar geometría. 
/// \brief \~english A structure to specify geometry.
struct ImmediateGeometry
{   
    /// Vertices
    VertexArray vertices {};

    /// Indices
    IndexArray indices {};

    /// \brief \~spanish Construye un objeto vacío.
    /// \brief \~english Construct emtpy geometry.
    ImmediateGeometry() = default;

    /// \brief \~spanish Construye un objeto con las listas de vértices e índices dadas.
    /// \brief \~english Construct geometry with given vertices and indices.
    /**
     * \~spanish
     * \param v arreglo de vértices.
     * \param i arreglo de índices.
     * 
     * \~english
     * \param v a vertex array.
     * \param i an index array.
    */
    ImmediateGeometry(VertexArray const& v, IndexArray const& i) 
        : vertices(v), indices(i) {}

    /// \~spanish Construye un triángulo en formato XYZRGB. \~english Construct triangle in XYZRGB format.
    static ImmediateGeometry rainbowTriangle();


    /// \~spanish Construye un trángulo en formato XYZ (sin colores). \~english Construct triangle in XYZ format (no color).
    static ImmediateGeometry triangle();
};

} // namespace folk


#endif // FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP