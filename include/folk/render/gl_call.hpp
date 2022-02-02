//
// Created by sergio on 01-02-22.
//

#ifndef INCLUDE_FOLK_RENDER__GL_CALL_HPP
#define INCLUDE_FOLK_RENDER__GL_CALL_HPP

#include "gl.hpp"

#include <type_traits>

namespace Folk {

struct gl final {

    gl() = delete;

    template<auto Function, class... Args>
    static auto call(const char *file, int line, const char *function, Args&&... args) -> decltype(Function(args...))
    {
        s_file = file;
        s_line = line;
        s_function = function;

        return Function(args...);
    }

    static constexpr const char* errorString(GLenum error);

#ifdef FOLK_DEBUG
private:
    static const char *s_file;
    static int s_line;
    static const char *s_function;
#endif
};


#ifdef FOLK_DEBUG
#define FOLK_GL_CALL(function, ...) gl::call<function>(__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)
#else // FOLK_DEBUG
#define FOLK_GL_CALL(function, ...) function(##__VA_ARGS__)
#endif // FOLK_DEBUG

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__GL_CALL_HPP
