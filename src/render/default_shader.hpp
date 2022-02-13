#ifndef FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP
#define FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP

namespace Folk
{

constexpr const char default_vert_source_code[] {
R"glsl(

#version 330 core

in vec3 a_position;

void main() {
    gl_Position = vec4(a_position, 1.0);
}

)glsl"
};


constexpr const char default_frag_source_code[] {
R"glsl(

#version 330 core

out vec4 frag_color;

void main() {
    frag_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

)glsl"
};

} // namespace Folk


#endif // FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP