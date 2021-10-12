#include "folk/render/material.hpp"
#include "folk/core/error.hpp"
#include "../core/engine_singleton.hpp"

namespace folk
{

static const char* default_vertex_shader_src = R"gl(
    #version 330 core
    layout (location = 0) in vec3 pos;

    void main() {
        gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
    }
)gl";

static const char* default_fragment_shader_src = R"gl(
    #version 330 core
    
    out vec4 finalColor;

    void main() {
        finalColor = vec4(1, 1, 1, 1);
    }
)gl";

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

Material::Ref Material::createDefaultMaterial() {
    Material::VertexAttribArray arr = {
        {0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0}
    };

    return Material::create(
            default_vertex_shader_src, 
            default_fragment_shader_src,
            arr
        );
};

Material::Ref Material::create(const char* vert, const char* frag, 
                                VertexAttribArray &arr)
{
    return Ref(new Material(vert, frag, arr));
}

Material::Material(const char* vert_src, const char* frag_src,
                    VertexAttribArray &arr)
    : vertex_attributes(arr)
{
    // compile vertex shader
    auto vertex_shader = compileShader(GL_VERTEX_SHADER, 
                                    vert_src);

    auto fragment_shader = compileShader(GL_FRAGMENT_SHADER,
                                    frag_src);

    program = glCreateProgram();
    ENGINE.out << "Created program: " << program;

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
}

Material::~Material() {
    glDeleteProgram(program);
}
    
} // namespace folk
