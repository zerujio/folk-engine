#include "folk/render/shader.hpp"
#include "folk/core/error.hpp"
#include "common.hpp"
#include "renderer.hpp"
#include "shader_data.hpp"
#include "default_shader.hpp"

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

static const bgfx::ProgramHandle buildProgram(const bgfx::ShaderHandle vert, 
                                        const bgfx::ShaderHandle frag)
{       
    auto program = bgfx::createProgram(vert, frag, true);

    if (!bgfx::isValid(program))
        throw EngineRuntimeError("Shader program linking failed");

    return program;
}

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
