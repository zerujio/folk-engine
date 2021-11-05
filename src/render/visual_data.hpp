#ifndef FOLK_RENDER__VISUAL_DATA_HPP
#define FOLK_RENDER__VISUAL_DATA_HPP

#include "folk/render/visual.hpp"

namespace Folk
{

struct VisualData final : public Visual {
    VisualData(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
        : Visual(mesh, material)
    {}
};

} // namespace Folk


#endif // FOLK_RENDER__VISUAL_DATA_HPP