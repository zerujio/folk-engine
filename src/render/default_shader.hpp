#ifndef FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP
#define FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP

namespace Folk
{

constexpr const char default_vert_source_code[] {
R"glsl(

#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

)glsl"
};


constexpr const char default_frag_source_code[] {
R"glsl(

#version 330 core

void main() {}

)glsl"
};

} // namespace Folk


#endif // FOLK_RENDER__DEFAULT_HEADER_SOURCE_HPP