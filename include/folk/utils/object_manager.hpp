//
// Created by sergio on 02-02-22.
//

#ifndef INCLUDE_FOLK_UTILS__OBJECT_MANAGER_HPP
#define INCLUDE_FOLK_UTILS__OBJECT_MANAGER_HPP

#include "object_handle.hpp"

namespace Folk {

/**
 * @brief Base class for OpenAL object managers.
 * A manager differs from
 * @tparam HandleType A handle type that inherits from ObjectHandle.
 * @tparam Gen The function to generate new objects of this type (e.g. alGenSources).
 * @tparam Del The function to delete objects (e.g. alDeleteSources).
 */
template<class HandleType, auto Gen, auto Del>
class ObjectManager : public HandleType {

    using Call = typename HandleType::Call;
    using HandleType::id;

public:
    /// Creates an OpenAL object.
    ObjectManager() {
        Call::slow(Gen)(1, &m_id());
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
        if (id() && static_cast<HandleType*>(this)->valid())
            Call::slowNoExcept(Del)(1, &m_id());
    }

private:
    [[nodiscard]] constexpr ALuint& m_id() noexcept {
        return static_cast<HandleType*>(this)->m_id;
    }
};

} // namespace Folk

#endif //INCLUDE_FOLK_UTILS__OBJECT_MANAGER_HPP
