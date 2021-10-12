#ifndef FOLK_RENDER__MATERIAL_HPP
#define FOLK_RENDER__MATERIAL_HPP

#include "folk/core/resource.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

namespace folk
{

/// Determines the way a Mesh is rendered.
/**
 * A material groups shaders, textures, and other shader parameters.
*/
class Material : public Resource {

public:
    struct VertexAttrib {
        GLuint location;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        GLuint64 offset;
    };

    using VertexAttribArray = std::vector<VertexAttrib>;

    using Ref = Reference<Material>;
    
    static Ref createDefaultMaterial();
    
    static Ref create(const char*, const char*, VertexAttribArray&);

    ~Material();

private:
    VertexAttribArray vertex_attributes;

    GLuint program;
    Material(const char*, const char*, VertexAttribArray&);

    friend class Visual;
    friend class RenderModule;
};

} // namespace folk


#endif//FOLK_RENDER__MATERIAL_HPP