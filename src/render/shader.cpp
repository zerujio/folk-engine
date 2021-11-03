#include "folk/render/shader.hpp"
#include "folk/core/error.hpp"
#include "common.hpp"
#include "renderer.hpp"
#include "shader_src.hpp"

#include <fstream>
#include <sstream>

#include <iostream>

namespace Folk
{

static const bgfx::ShaderHandle loadShaderFile(const char* filename) {
    std::ifstream file {filename, std::ios::binary};

    if (!file.is_open())
        throw EngineRuntimeError("Couldn't open file " + std::string(filename));

    file.seekg(0, std::ios::end);
    std::size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* data = new char[file_size + 1];
    data[file_size] = '\0';

    file.read(data, file_size);

    auto mem = bgfx::makeRef(data, file_size + 1,
                             [](void* ptr, void* _d) { delete[] (char*) ptr; });
    
    auto handle = bgfx::createShader(mem);
    if (!bgfx::isValid(handle))
        throw EngineRuntimeError("Shader load failed");
    
    bgfx::setName(handle, filename);

    return handle;
}

static bgfx::ProgramHandle buildProgram(const bgfx::ShaderHandle vert, 
                                        const bgfx::ShaderHandle frag)
{       
    auto program = bgfx::createProgram(vert, frag, true);

    if (!bgfx::isValid(program))
        throw EngineRuntimeError("Shader program linking failed");

    return program;
}

Shader::Shader(const char* vert_filename, const char* frag_filename)
{
    RENDER.shaders[id] = {buildProgram(loadShaderFile(vert_filename),
                                       loadShaderFile(frag_filename))};
}

// default shader
Shader::Shader() {
    auto vmem = bgfx::makeRef(vs_default, sizeof(vs_default));
    auto vert = bgfx::createShader(vmem);

    auto fmem = bgfx::makeRef(fs_default, sizeof(fs_default));
    auto frag = bgfx::createShader(fmem);

    RENDER.shaders[id] = {buildProgram(frag, vert)};
}

Shader::~Shader() {
    bgfx::destroy(RENDER.shaders[id].program_handle);
    
    RENDER.shaders.erase(id);
}

Shader::Ref Shader::createFromFiles(const char* vertex_file,
                                    const char* fragment_file)
{
    return {new Shader(vertex_file, fragment_file)}; 
}

Shader::Ref Shader::createDefault() {
    return {new Shader()};
}

} // namespace Folk
