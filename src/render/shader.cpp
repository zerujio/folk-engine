#include "folk/render/shader.hpp"
#include "renderer.hpp"

namespace Folk
{

Shader::Ref Shader::createDefault() {
    return std::make_shared<Shader>();
}

Shader::Ref Shader::createFromFiles(const char* vert, const char* frag) {
    return std::make_shared<Shader>();
}

} // namespace Folk
