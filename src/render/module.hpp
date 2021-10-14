#ifndef FOLK_RENDER__MODULE_HPP
#define FOLK_RENDER__MODULE_HPP

#include "../utils/singleton.hpp"
#include "../utils/update_listener.hpp"

#include "shader_data.hpp"
#include "mesh_data.hpp"
#include "visual_data.hpp"

#include <map>

namespace Folk {

FOLK_SINGLETON_CLASS_FINAL(RenderModule), public UpdateListener {
public:
    std::map<Shader::Id, ShaderData> shaders {};
    std::map<Mesh::Id, MeshData> meshes {};
    std::map<Visual::Id, VisualData> visuals {};

private:
    friend class EngineSingleton;

    RenderModule();

    void update(Delta) override;
};

} // namespace folk

#define RENDER RenderModule::instance()

#endif//FOLK_RENDER__MODULE_HPP