#include "folk/render/shader.hpp"
#include "folk/core/error.hpp"
#include "common.hpp"
#include "renderer.hpp"
#include "shader_data.hpp"
#include "default_shader.hpp"
#include "shader_loader.hpp"

namespace Folk
{

Shader::Ref Shader::createDefault() {
    std::shared_ptr<ShaderData> data_ptr =
            std::make_shared<ShaderData>(getDefaultProgramHandle());
    return std::shared_ptr<Shader>(data_ptr, data_ptr.get());
}

Shader::Ref Shader::createFromFiles(const char* vert, const char* frag) {
    auto handle = buildProgram(loadShaderFile(vert), loadShaderFile(frag));
    auto ptr = std::make_shared<ShaderData>(handle);
    return {ptr, ptr.get()};
}

} // namespace Folk
