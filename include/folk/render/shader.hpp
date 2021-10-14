#ifndef FOLK_RENDER__SHADER_HPP
#define FOLK_RENDER__SHADER_HPP

#include "folk/core/resource.hpp"

#include <vector>

namespace Folk
{

class Shader : public Resource
{
public:
    struct VertexAttrib {
        enum class Type { Float, Int, Uint };

        uint location;
        int size;
        Type type;
        bool normalized;
        int stride;
        uint offset;
    };

    using VertexAttribArray = std::vector<VertexAttrib>;
    using Ref = Reference<Shader>;

    static Ref createDefaultShader();
    static Ref create(const char*, const char*, VertexAttribArray const&);

    ~Shader();

private:
    VertexAttribArray vaa;

    Shader(const char*, const char*, VertexAttribArray const&);

    friend Ref;
    friend class Material;
    friend class Visual;
    friend class RenderModule;
};

} // namespace Folk


#endif // FOLK_RENDER__SHADER_HPP