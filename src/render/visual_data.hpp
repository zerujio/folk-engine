#ifndef FOLK_RENDER__VISUAL_DATA_HPP
#define FOLK_RENDER__VISUAL_DATA_HPP

#include "folk/render/visual.hpp"
#include "common.hpp"

namespace Folk
{

struct VisualData {
    GLuint vao;

    VisualData(GLuint vao_) : vao(vao_) {}
};

} // namespace Folk


#endif // FOLK_RENDER__VISUAL_DATA_HPP