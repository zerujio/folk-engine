//
// Created by sergio on 06-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__INDEX_TYPES_HPP
#define INCLUDE_FOLK_RENDER__INDEX_TYPES_HPP

#include "gl.hpp"

namespace Folk {

/// Valid location types.
enum class IndexType : GLenum {
    UInt16 = GL_UNSIGNED_SHORT,
    UInt32 = GL_UNSIGNED_INT
};

template<class T> constexpr IndexType getIndexTypeOf() {
    constexpr bool is_short = std::is_same_v<T, GLushort>;
    constexpr bool is_int = std::is_same_v<T, GLuint>;

    static_assert( is_short || is_int, "Index type must be GLuint or GLushort" );

    if constexpr (is_short)
        return IndexType::UInt16;
    else
        return IndexType::UInt32;
}

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__INDEX_TYPES_HPP
