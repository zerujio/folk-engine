#ifndef FOLK_RENDER__SHADER_DATA_HPP
#define FOLK_RENDER__SHADER_DATA_HPP

#include "folk/render/shader.hpp"
#include "common.hpp"

namespace Folk
{

static constexpr GLenum toGLenum(Shader::VertexAttrib::Type);

struct ShaderData {
    struct VertexAttrib {
        GLuint location;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        GLuint64 offset;

        VertexAttrib() = default;

        VertexAttrib(Shader::VertexAttrib const& va) 
            : location(va.location), 
            size(va.size), 
            type(toGLenum(va.type)),
            normalized(va.normalized ? GL_TRUE : GL_FALSE),
            stride(va.stride), 
            offset(va.offset)
        {}
    };

    using VertexAttribArray = std::vector<VertexAttrib>;

    ShaderData(GLuint program_, VertexAttribArray const& vaa_)
        : program(program_), vaa(vaa_)
    {}

    ShaderData(GLuint program_, Shader::VertexAttribArray const& vaa_) 
        : program(program_), vaa()
    {
        for (auto& va : vaa_)
            vaa.emplace_back(va);
    }

    GLuint program;
    VertexAttribArray vaa;
};

// helper functions

constexpr GLenum toGLenum(Shader::VertexAttrib::Type t) {
    using Type = Shader::VertexAttrib::Type;

    switch (t)
    {
    default:
    case Type::Float:
        return GL_FLOAT;

    case Type::Int:
        return GL_INT;
    
    case Type::Uint:
        return GL_UNSIGNED_INT;
    }
}

} // namespace Folk


#endif // FOLK_RENDER__SHADER_DATA_HPP