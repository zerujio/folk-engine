#include "default_shader.hpp"
#include "default_shader_source.h"

#include "folk/core/error.hpp"

namespace Folk
{

template <std::size_t N>
static const bgfx::ShaderHandle buildShader(const uint8_t (&data)[N],
                                            const char* name) {
    auto mem = bgfx::makeRef(data, N);
    auto handle = bgfx::createShader(mem);

    if (!bgfx::isValid(handle)) {
        throw CriticalEngineError("default shader creation failed");
    }

    bgfx::setName(handle, name);

    return handle;
}

static const bgfx::ProgramHandle buildProgram(bgfx::ShaderHandle vert,
                                              bgfx::ShaderHandle frag)
{
    auto handle = bgfx::createProgram(vert, frag, true);

    if (!bgfx::isValid(handle)) {
        throw CriticalEngineError("default shader linking failed");
    }

    return handle;
}
const bgfx::ProgramHandle getDefaultProgramHandle() {
    return buildProgram(buildShader(vs_default, "default vertex shader"), 
                        buildShader(fs_default, "default fragment shader"));
}

} // namespace Folk
