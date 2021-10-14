#ifndef FOLK_UTILS__RESOURCE_HPP
#define FOLK_UTILS__RESOURCE_HPP

#include "folk/utils/reference_counting.hpp"
#include "folk/utils/thread_safe_counter.hpp"

#include <mutex>

namespace Folk {

/// Base clase for resources like meshes, textures, and shaders.
/**
 * Resources are mutex protected, reference counted objects. The reference count 
 * is also thread safe, protected with a separate mutex.
*/
class Resource : public ReferenceCountedObject<ThreadSafeCounter<int>> {
public:
    using Id = unsigned int;

    const Id id;

protected:
    std::mutex mutex {};

    Resource() : id(++next_id) {}

private:
    static Id next_id;
};

}

#endif // FOLK_UTILS__RESOURCE_HPP