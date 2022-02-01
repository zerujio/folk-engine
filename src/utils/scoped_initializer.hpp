//
// Created by sergio on 30-01-22.
//

#ifndef SRC_UTILS__SCOPED_INITIALIZER_HPP
#define SRC_UTILS__SCOPED_INITIALIZER_HPP

#include <type_traits>

namespace Folk {

/// Calls initialize() when constructed and terminate() when destroyed.
template<class C>
struct ScopedInitializer final {

    template <class... Args>
    ScopedInitializer(Args&&... args) {
        C::initialize(std::forward<Args>(args)...);
    }

    ~ScopedInitializer() {
        C::terminate();
    }

    ScopedInitializer(const ScopedInitializer&) = delete;
    ScopedInitializer& operator=(const ScopedInitializer&) = delete;
};

} // namespace

#endif //SRC_UTILS__SCOPED_INITIALIZER_HPP
