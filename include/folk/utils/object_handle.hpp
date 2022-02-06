//
// Created by sergio on 02-02-22.
//

#ifndef INCLUDE_FOLK_UTILS__OBJECT_HANDLE_HPP
#define INCLUDE_FOLK_UTILS__OBJECT_HANDLE_HPP

#include "folk/error.hpp"

namespace Folk {

/**
 * @brief Base class for non owning handles.
 * @tparam LibCall The class that provides lambdas/function pointers for library calls.
 * @tparam isValid A function that checks the validity of the handle, such as glIsBuffer().
 * @tparam IdType The type for the handle, such as GLuint.
 */
template<class LibCall, auto isValid, class IdType>
class ObjectHandle {

    template<class H, auto G, auto D>
    friend class ObjectManager;

public:
    using id_t = IdType;
    using bool_t = decltype(isValid(0));

    /// Default constructor: id will default to zero, which may or may not be a valid id.
    ObjectHandle() : m_id(0) {}

    /// Checks the handle refers to a valid object of the correct type.
    [[nodiscard]] auto valid() const {
        return isValid(m_id);
    }

    [[nodiscard]] explicit operator bool() const {
        return valid();
    }

protected:
    using call = LibCall;

    /// Retrieve a property using an glGet-style function.
    template<class T, auto Getter, class Enum>
    [[nodiscard]] T get(Enum property) const {
        T value;
        LibCall::fast(Getter)(m_id, property, &value);
        return value;
    }

    template<class T, auto Setter, class Enum>
    void set(Enum property, T value) const {
        LibCall::fast(Setter)(m_id, property, value);
    }

    template<class VectorT, auto GetterV, class Enum>
    VectorT getV(Enum property) const {
        VectorT vector;
        LibCall::fast(GetterV)(m_id, property, &vector.x);
        return vector;
    }

    template<class VectorT, auto SetterV, class Enum>
    void setV(Enum property, const VectorT vector) const {
        LibCall::fast(SetterV)(m_id, property, &vector.x);
    }

    constexpr auto id() const {
        return m_id;
    }

    constexpr ObjectHandle(IdType id) : m_id(id) {}

private:
    IdType m_id {0};
};

} // namespace Folk

#endif //INCLUDE_FOLK_UTILS__OBJECT_HANDLE_HPP
