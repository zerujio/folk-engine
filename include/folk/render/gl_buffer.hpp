//
// Created by sergio on 05-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_BUFFER_HPP
#define INCLUDE_FOLK_RENDER__GL_BUFFER_HPP

#include "gl_object.hpp"

namespace Folk::gl {

GLboolean isBuffer(GLuint id);

enum class BufferTarget : GLenum {
    Array = GL_ARRAY_BUFFER,
    AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
    CopyRead = GL_COPY_READ_BUFFER,
    CopyWrite = GL_COPY_WRITE_BUFFER,
    DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
    DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
    ElementArray = GL_ELEMENT_ARRAY_BUFFER,
    PixelPack = GL_PIXEL_PACK_BUFFER,
    PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
    ShaderStorage = GL_SHADER_STORAGE_BUFFER,
    Texture = GL_TEXTURE_BUFFER,
    TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
    Uniform = GL_UNIFORM_BUFFER
};

class BufferHandle : public BaseHandle<isBuffer> {

public:
    /// Bind to a buffer target. LibCall type: fast.
    void bind(BufferTarget) const;

    /// Unbind a target's current buffer.
    static void unbind(BufferTarget target);
};

void genBuffers(GLsizei n, GLuint* id_array);
void deleteBuffers(GLsizei n, GLuint* id_array);

using BufferManager = ObjectManager<BufferHandle, genBuffers, deleteBuffers>;

} // namespace Folk::gl

#endif //INCLUDE_FOLK_RENDER__GL_BUFFER_HPP
