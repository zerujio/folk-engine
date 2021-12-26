#include "default_shader.hpp"
#include "default_shader_source.h"

#include "folk/error.hpp"

namespace Folk
{

template <std::size_t N>
static const bgfx::ShaderHandle buildShader(const uint8_t (&data)[N],
                                            const char* name) {
    auto mem = bgfx::makeRef(data, N);
    auto handle = bgfx::createShader(mem);

    if (!bgfx::isValid(handle)) {
        throw FOLK_CRITICAL_ERROR("default shader creation failed");
    }

    bgfx::setName(handle, name);

    return handle;
}

static const bgfx::ProgramHandle buildProgram(bgfx::ShaderHandle vert,
                                              bgfx::ShaderHandle frag)
{
    auto handle = bgfx::createProgram(vert, frag, true);

    if (!bgfx::isValid(handle)) {
        throw FOLK_CRITICAL_ERROR("default shader linking failed");
    }

    return handle;
}
const bgfx::ProgramHandle getDefaultProgramHandle() {
    bgfx::ShaderHandle vertex {};
    bgfx::ShaderHandle fragment {};

    switch (bgfx::getRendererType())
    {
    case bgfx::RendererType::OpenGL:
        vertex = buildShader(glsl::vs_basic, "default glsl vertex shader");
        fragment = buildShader(glsl::fs_basic, "default glsl fragment shader");
        break;
    
    case bgfx::RendererType::Vulkan:
        vertex = buildShader(spirv::vs_basic, "default vulkan vertex shader");
        fragment = buildShader(spirv::fs_basic, "default vulkan fragment shader");
        break;
    
    default:
        throw FOLK_RUNTIME_ERROR("Unsupported rendering backend!");
        break;
    }

    return buildProgram(vertex, fragment);
}

} // namespace Folk
