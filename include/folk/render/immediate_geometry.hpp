#ifndef FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP
#define FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP

#include <vector>
#include <cstdint>

namespace Folk
{

/// \brief \~spanish Una estructura para especificar geometría. 
/// \brief \~english A structure to specify geometry.
struct ImmediateGeometry
{   
    struct Vertex {
        float x;
        float y;
        float z;
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Vertex(float x_, float y_, float z_, uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)
            : x(x_), y(y_), z(z_), r(r_), g(g_), b(b_), a(a_)
        {}

        Vertex(float x_, float y_, float z_, uint32_t color_) {
            color() = color_;
        }

        uint32_t& color() {
            return *((uint32_t*) &r);
        }
    };

    static_assert(sizeof(Vertex) == 16);

    using VertexArray = std::vector<Vertex>;

    using Index = uint16_t;
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
    ImmediateGeometry(VertexArray && v, IndexArray && i) 
        : vertices(v), indices(i) {}

    /// Genera un cuadrado multicolor
    static ImmediateGeometry colorSquare();
};

} // namespace folk


#endif // FOLK_RENDER__IMMEDIATE_GEOMETRY_HPP