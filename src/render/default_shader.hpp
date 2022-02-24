#ifndef FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP
#define FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP

namespace Folk
{

constexpr const char default_vert_source_code[] {
R"glsl(

#version 330 core

in vec3 a_position;
in vec2 a_texCoord;

out vec2 texCoord;

void main() {
    gl_Position = vec4(a_position, 1.0);
    texCoord = a_texCoord;
}

)glsl"
};


constexpr const char default_frag_source_code[] {
R"glsl(

#version 330 core

in vec2 texCoord;

out vec4 frag_color;
uniform vec4 u_color;
uniform sampler2D u_texture;

void main() {
    frag_color = texture(u_texture, texCoord) * u_color;
}

)glsl"
};

} // namespace Folk


#endif // FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP