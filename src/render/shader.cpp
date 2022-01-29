#include "folk/render/shader.hpp"
#include "folk/error.hpp"
#include "common.hpp"
#include "renderer.hpp"
#include "default_shader.hpp"
#include "shader_loader.hpp"

namespace Folk
{

Shader::Ref Shader::createDefault() {
    return std::make_shared<Shader>();
}

Shader::Ref Shader::createFromFiles(const char* vert, const char* frag) {
    return std::make_shared<Shader>();
}

} // namespace Folk
