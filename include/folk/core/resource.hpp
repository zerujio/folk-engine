#ifndef FOLK_UTILS__RESOURCE_HPP
#define FOLK_UTILS__RESOURCE_HPP

#include "folk/utils/thread_safe_counter.hpp"
#include "folk/error.hpp"

#include <mutex>
#include <memory>

namespace Folk {

/// Clase base para recursos como mallas, texturas y shaders.
/**
 * Estos objetos no están pensados para ser manipulados directamente, sino a 
 * través de una referencia (std::shared_ptr).
*/
class Resource {
public:
    Resource(Resource const&) = delete;
    Resource& operator=(Resource const&) = delete;

protected:
    Resource() = default;
    std::mutex mtx {};
};

}

#endif // FOLK_UTILS__RESOURCE_HPP