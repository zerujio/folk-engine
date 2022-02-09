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

    using CreateT = decltype(Create);
    static constexpr bool glGenStyle { std::is_invocable_v<CreateT, int, id_t*, Args...> };
    static constexpr bool glCreateStyle {
        std::is_invocable_v<CreateT, Args...>&& std::is_same_v<id_t, std::invoke_result_t<CreateT, Args...>>
    };
    static constexpr bool unknownStyle { !glGenStyle && !glCreateStyle };

protected:

    using Call = typename HandleType::Call;
    using HandleType::valid;
    using HandleType::id;
    using Id = typename HandleType::Id;

public:
    /// Creates an OpenAL object.
    explicit ObjectManager(Args... args) {

        if constexpr(glGenStyle) {
            // function has glGenBuffers style signature
            Call::slow(Create)(1, &m_id(), args...);

        } else if constexpr(glCreateStyle) {
            // function has glCreateShader style signature
            m_id() = Call::slow(Create)(args...);

        } else {
            static_assert(unknownStyle,
                    "'Create' function signature does not match any known style;"
                    " perhaps the argument types are incorrect?");
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
            if constexpr(glGenStyle)
                Call::slowNoExcept(Destroy)(1, &m_id());
            else if constexpr(glCreateStyle)
                Call::slowNoExcept(Destroy)(id());
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
