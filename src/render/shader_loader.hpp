#ifndef FOLK_RENDER__SHADER_LOADER_HPP
#define FOLK_RENDER__SHADER_LOADER_HPP

#include "common.hpp"

namespace Folk
{

const bgfx::ShaderHandle loadShaderFile(const char* filename);
const bgfx::ProgramHandle buildProgram(const bgfx::ShaderHandle vert, const bgfx::ShaderHandle frag);

} // namespace Folk


#endif // FOLK_RENDER__SHADER_LOADER_HPP