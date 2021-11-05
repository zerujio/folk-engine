#ifndef FOLK_RENDER__SHADER_DATA_HPP
#define FOLK_RENDER__SHADER_DATA_HPP

#include "folk/render/shader.hpp"

#include "common.hpp"

namespace Folk
{

struct ShaderData final : public Shader {
    const bgfx::ProgramHandle program_handle;

    ShaderData(const bgfx::ProgramHandle p) : program_handle(p) {}

    ~ShaderData() {
        bgfx::destroy(program_handle);
    }
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_DATA_HPP