#include "folk/render/shader.hpp"
#include "folk/error.hpp"
#include "common.hpp"
#include "renderer.hpp"
#include "default_shader.hpp"
#include "shader_loader.hpp"

namespace Folk
{

Shader::Shader(const bgfx::ProgramHandle handle_) : handle(handle_) {}

Shader::~Shader() {
    bgfx::destroy(handle);
}

Shader::Ref Shader::createDefault() {
    return std::make_shared<Shader>(getDefaultProgramHandle());
}

Shader::Ref Shader::createFromFiles(const char* vert, const char* frag) {
    auto handle = buildProgram(loadShaderFile(vert), loadShaderFile(frag));
    return std::make_shared<Shader>(handle);
}

} // namespace Folk
