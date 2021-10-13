#include "folk/render/visual.hpp"
#include "../core/engine_singleton.hpp"

namespace Folk
{

Visual::Ref Visual::create(MeshRef mesh_, MaterialRef material_) {
    return new Visual(mesh_, material_);
}

Visual::Visual(MeshRef mesh_, MaterialRef material_) 
    : mesh(mesh_), material(material_) 
{
    // this is single threaded!
    glGenVertexArrays(1, &vao);
    // ENGINE.out << "Created VAO: " << vao << "\n";

    bindBuffers();
    enableVertexAttributes();
}

Visual::Visual(Visual const& other) : Visual(other.mesh, other.material) {}

Visual::~Visual()
{
    glDeleteVertexArrays(1, &vao);
    // ENGINE.out << "Deleted VAO:" << vao << "\n";
}

Visual& Visual::operator=(Visual const& other) {
    mesh = other.mesh;
    material = other.material;
    bindBuffers();
    enableVertexAttributes();

    return *this;
}

void Visual::setMesh(MeshRef const& new_mesh) {
    mesh = new_mesh;
    bindBuffers();
}

Visual::MeshRef Visual::getMesh() {
    return mesh;
}

void Visual::setMaterial(MaterialRef const& new_material) {
    material = new_material;
    enableVertexAttributes();
}

Visual::MaterialRef Visual::getMaterial() {
    return material;
}

void Visual::bindBuffers() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBindVertexArray(0);

    /* 
        ENGINE.out << "Bound VBO=" << mesh->vbo 
            << " and EBO=" << mesh->ebo
            << " to VAO=" << vao << "\n";
     */
}

void Visual::enableVertexAttributes() {
    glBindVertexArray(vao);
    // ENGINE.out << "Enabled attribute locations ";
    for (auto& a : material->vertex_attributes) {
        glVertexAttribPointer(
            a.location,
            a.size,
            a.type,
            a.normalized,
            a.stride,
            (void*) a.offset
        );
        glEnableVertexAttribArray(a.location);
        // ENGINE.out << a.location << ", ";
    }
    // ENGINE.out << " in VAO=" << vao << "\n";
    glBindVertexArray(0);
}

} // namespace folk
