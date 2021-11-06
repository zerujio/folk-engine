#include "folk/core/error.hpp"

#include "shader_loader.hpp"

#include "common.hpp"

#include <fstream>

namespace Folk
{

const bgfx::ShaderHandle loadShaderFile(const char* filename) {
    std::ifstream file {filename, std::ios::binary};

    if (!file.is_open())
        throw EngineRuntimeError("Couldn't open file " + std::string(filename));

    file.seekg(0, std::ios::end);
    std::size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    auto mem = bgfx::alloc(file_size + 1);
    file.read((char*) mem->data, file_size);
    mem->data[file_size] = '\0';

    file.close();

    auto handle = bgfx::createShader(mem);

    if (!bgfx::isValid(handle))
        throw EngineRuntimeError("Shader load failed");
    
    bgfx::setName(handle, filename);

    return handle;
}

const bgfx::ProgramHandle buildProgram(const bgfx::ShaderHandle vert, 
                                        const bgfx::ShaderHandle frag)
{       
    auto program = bgfx::createProgram(vert, frag, true);

    if (!bgfx::isValid(program))
        throw EngineRuntimeError("Shader program linking failed");

    return program;
}

} // namespace Folk