#include "folk/render/visual.hpp"
#include "../core/engine_singleton.hpp"
#include "module.hpp"

namespace Folk
{

/// raii binding owo
struct VAObind {
    VAObind(GLuint vao) {
        glBindVertexArray(vao);
    }

    ~VAObind() {
        glBindVertexArray(0);
    }
};

Visual::Ref Visual::create(Mesh::Ref mesh_, Material::Ref material_) {
    return Ref(new Visual(mesh_, material_));
}

Visual::Visual(Mesh::Ref mesh_, Material::Ref material_) 
    : mesh(mesh_), material(material_) 
{
    GLuint vao;
    glGenVertexArrays(1, &vao);

    VAObind bind {vao};
    // ENGINE.out << "Created VAO: " << vao << "\n";
    RENDER.visuals.emplace(id, vao);

    bindBuffers();
    enableVertexAttributes();
}

Visual::~Visual()
{
    auto data = RENDER.visuals.at(id);

    if (data.vao)
        glDeleteVertexArrays(1, &(data.vao));
    // ENGINE.out << "Deleted VAO:" << vao << "\n";

    RENDER.visuals.erase(id);
}

Visual::Visual(Visual const& other) 
    : Visual(other.mesh, other.material) 
{}

Visual& Visual::operator=(Visual const& other) {
    mesh = other.mesh;
    material = other.material;

    VisualData& data = RENDER.visuals.at(id);
    
    {
        VAObind bind {data.vao};
        bindBuffers();
        enableVertexAttributes();
    }

    return *this;
}

Visual::Visual(Visual && other) 
    : mesh(other.mesh), material(other.material)
{
    auto& other_data = RENDER.visuals.at(other.id);
    RENDER.visuals.emplace(id, other_data);

    other_data.vao = 0;
}

Visual& Visual::operator=(Visual&& other)
{
    mesh = other.mesh;
    material = other.material;

    auto& data = RENDER.visuals.at(id);
    auto& other_data = RENDER.visuals.at(other.id);

    data = other_data;
    other_data = 0;

    return *this;
}

void Visual::setMesh(Mesh::Ref new_mesh) {
    mesh = new_mesh;
    VAObind bind {RENDER.visuals.at(id).vao};
    bindBuffers();
}

Mesh::Ref Visual::getMesh() const {
    return mesh;
}

void Visual::setMaterial(Material::Ref new_material) {
    material = new_material;
    VAObind bind {RENDER.visuals.at(id).vao};
    enableVertexAttributes();
}

Material::Ref Visual::getMaterial() const {
    return material;
}

void Visual::bindBuffers() {
    MeshData& data = RENDER.meshes.at(mesh->id);

    glBindBuffer(GL_ARRAY_BUFFER, data.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ebo);

    /* 
        ENGINE.out << "Bound VBO=" << mesh->vbo 
            << " and EBO=" << mesh->ebo
            << " to VAO=" << vao << "\n";
     */
}

void Visual::enableVertexAttributes() {
    ShaderData& data = RENDER.shaders.at(material->shader->id);
    GLuint vao = RENDER.visuals.at(id).vao;

    VAObind bind {vao};
    // ENGINE.out << "Enabled attribute locations ";
    for (auto& a : data.vaa) {
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
    
}

} // namespace folk
