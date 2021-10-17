#ifndef FOLK_UTILS__RESOURCE_HPP
#define FOLK_UTILS__RESOURCE_HPP

#include "folk/utils/reference_counting.hpp"
#include "folk/utils/thread_safe_counter.hpp"

#include <mutex>

namespace Folk {

/// \brief \~spanish Clase base para recursos como mallas, texturas y shaders.
/// \brief \~english Base clase for resources like meshes, textures, and shaders.
/**
 * \~spanish
 * Un recurso es un objeto con conteo de referencias y mecanismos de exclusión mutua. 
 * El contador de referencias tiene un mutex distinto al resto del recurso.
 * 
 * \~english
 * Resources are mutex protected, reference counted objects. The reference count 
 * is also thread safe, protected with a separate mutex.
*/
class Resource : public ReferenceCountedObject<ThreadSafeCounter<uint>> {
public:
    using Id = ThreadSafeCounter<uint>;

    const Id id;

protected:
    std::mutex mutex {};

    Resource() : id(++next_id) {}

private:
    static Id next_id;
};

}

#endif // FOLK_UTILS__RESOURCE_HPP