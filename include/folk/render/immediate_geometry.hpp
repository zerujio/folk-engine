#ifndef FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP
#define FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP

#include <vector>

namespace Folk
{

/// \brief \~spanish Una estructura para especificar geometría. 
/// \brief \~english A structure to specify geometry.
template<class Vertex, class Index>
struct ImmediateGeometry
{
    using VertexArray = std::vector<Vertex>;
    using IndexArray = std::vector<Index>;

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
    ImmediateGeometry(VertexArray && v, IndexArray && i) : vertices(v), indices(i) {}
};

} // namespace folk


#endif // FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP