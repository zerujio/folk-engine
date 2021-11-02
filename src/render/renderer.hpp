#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "../core/module.hpp"

#include "shader_data.hpp"
#include "mesh_data.hpp"
#include "visual_data.hpp"

#include <functional>
#include <vector>
#include <map>

namespace Folk {

FOLK_ENGINE_UPDATEABLE_MODULE(Renderer){
public:
    std::map<Shader::Id, ShaderData> shaders {};
    std::map<Mesh::Id, MeshData> meshes {};
    std::map<Visual::Id, VisualData> visuals {};

    const char* name() const override {return "Renderer";}

private:
    friend class EngineSingleton;

    Renderer();
    ~Renderer();

    void update(Delta) override;

    int render_id;
};

} // namespace folk

#define RENDER RenderModule::instance()

#endif//FOLK_RENDER__MODULE_HPP