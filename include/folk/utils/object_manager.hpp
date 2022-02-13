//
// Created by sergio on 02-02-22.
//

#ifndef INCLUDE_FOLK_UTILS__OBJECT_MANAGER_HPP
#define INCLUDE_FOLK_UTILS__OBJECT_MANAGER_HPP

#include "object_handle.hpp"
#include <type_traits>

namespace Folk {

/**
 * @brief Base class for OpenAL object managers.
 * A manager differs from
 * @tparam HandleType A handle type that inherits from ObjectHandle.
 * @tparam Create The function to generate new objects of this type (e.g. alGenSources).
 * @tparam Destroy The function to delete objects (e.g. alDeleteSources).
 * @tparam Args Constructor arguments to forward to the Create() function.
 */

template<class HandleType, auto Create, auto Destroy, class... Args>
class ObjectManager : public HandleType {

    using Call = typename HandleType::Call;
    using HandleType::id;
    using Id = typename HandleType::Id;

public:
    using HandleType::valid;

    /// Creates an object.
    explicit ObjectManager(Args... args) {

        if constexpr(std::is_invocable_v<decltype(Create), Args...>) {
            // function has glCreateShader style signature
            m_id() = Call::slow(Create)(args...);

        } else {
            // function has glGenBuffers style signature
            Call::slow(Create)(1, &m_id(), args...);
        }
    }

    /// Deleted copy constructor.
    ObjectManager(const ObjectManager &) = delete;

    /// Takes ownership of another instance's object.
    ObjectManager(ObjectManager&& other) noexcept {
        m_id() = other.id();
        other.m_id() = 0;
    }

    /// Deleted copy assignment.
    ObjectManager& operator=(const ObjectManager&) = delete;

    /// Take ownership of another instance's object.
    ObjectManager& operator=(ObjectManager&& other) noexcept {
        m_id() = other.id();
        other.m_id() = 0;
        return *this;
    }

    /// Deletes the managed object.
    ~ObjectManager() {
        if (id() && valid()) {
            if constexpr(std::is_invocable_v<decltype(Destroy), Id>)
                Call::slowNoExcept(Destroy)(id());
            else
                Call::slowNoExcept(Destroy)(1, &m_id());
        }
    }

private:
    // access id data member
    [[nodiscard]] constexpr auto& m_id() noexcept {
        return static_cast<HandleType*>(this)->m_id;
    }
};

} // namespace Folk

#endif //INCLUDE_FOLK_UTILS__OBJECT_MANAGER_HPP
