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

enum class BufferUsage : GLenum {
    StaticDraw = GL_STATIC_DRAW,
    StaticRead = GL_STATIC_READ,
    StaticCopy = GL_STATIC_COPY,
    DynamicDraw = GL_DYNAMIC_DRAW,
    DynamicRead = GL_DYNAMIC_READ,
    DynamicCopy = GL_DYNAMIC_COPY,
    StreamDraw = GL_STREAM_DRAW,
    StreamRead = GL_STREAM_READ,
    StreamCopy = GL_STREAM_COPY
};

class Buffer : public BaseHandle<isBuffer> {

public:
    /// Bind to a buffer target. LibCall type: fast.
    void bind(BufferTarget) const;

    /// Unbind a target's current buffer.
    static void unbind(BufferTarget target);

    /// Copy data to buffer.
    static void data(BufferTarget target, GLsizei size, const void *data, BufferUsage usage);
};

void genBuffers(GLsizei n, GLuint* id_array);
void deleteBuffers(GLsizei n, GLuint* id_array);

using BufferManager = ObjectManager<Buffer, genBuffers, deleteBuffers>;

} // namespace Folk::gl

#endif //INCLUDE_FOLK_RENDER__GL_BUFFER_HPP
