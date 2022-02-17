//
// Created by sergio on 17-02-22.
//

#ifndef SRC_UTILS__DELETER_HPP
#define SRC_UTILS__DELETER_HPP

namespace Folk {

template <auto Func>
struct Deleter {
    template<typename T>
    constexpr void operator()(T* arg) const {
        Func(arg);
    }
};

} // namespace Folk

#endif //SRC_UTILS__DELETER_HPP
