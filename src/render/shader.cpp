#include "folk/render/shader.hpp"
#include "folk/core/error.hpp"
#include "common.hpp"
#include "module.hpp"

namespace Folk
{

static const char* default_vert_src = R"gl(
    #version 330 core
    layout (location = 0) in vec3 pos;

    void main() {
        gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
    }
)gl";

static const char* default_frag_src = R"gl(
    #version 330 core
    
    out vec4 finalColor;

    void main() {
        finalColor = vec4(1, 1, 1, 1);
    }
)gl";

static const Shader::VertexAttribArray default_vaa {
    {0, 3, Shader::VertexAttrib::Type::Float}
};

static GLuint compileShader(GLenum type, const char* src) {
    int success;
    int log_length;
    char log[512];

    GLuint shader = glCreateShader(type);

    if (!shader) {
        throw CriticalEngineError("Shader creation failed!");
    }

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, log_length, nullptr, log);
        glDeleteShader(shader);
        throw CriticalEngineError("Shader compilaton failed: " 
            + std::string(log));
    }

    return shader;
}

Shader::Ref Shader::createDefaultShader() {
    return Ref(new Shader(default_vert_src, default_frag_src, default_vaa));
}

Shader::Ref Shader::create(const char* vert, const char* frag, 
                           VertexAttribArray const& vaa)
{
    return Ref( new Shader(vert, frag, vaa) );
}

Shader::Shader(const char* vert, const char* frag,
               VertexAttribArray const& vaa)
{
        // compile vertex shader
    auto vertex_shader = compileShader(GL_VERTEX_SHADER, vert);

    auto fragment_shader = compileShader(GL_FRAGMENT_SHADER, frag);

    auto program = glCreateProgram();
    // ENGINE.out << "Created program: " << program;

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    int success;
    int logsize = 512;
    char log[logsize];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glad_glGetProgramInfoLog(program, logsize, nullptr, log);
        throw CriticalEngineError("Shader linking failed:" + std::string(log));
    }

    RENDER.shaders.emplace(id, ShaderData(program, vaa));
}

Shader::~Shader() 
{
    auto &data = RENDER.shaders.at(id);
    glDeleteProgram(data.program);
    RENDER.shaders.erase(id);
}

} // namespace Folk
