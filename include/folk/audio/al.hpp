#ifndef FOLK_AUDIO__OPEN_AL_HPP
#define FOLK_AUDIO__OPEN_AL_HPP

#include "folk/utils/library_call.hpp"

#include "AL/al.h"

#include <optional>

#define FOLK_AL_CALL(func, ...) FOLK_C_LIBRARY_CALL(al::getError, func, ##__VA_ARGS__)

/// Detalles de implementación
namespace Folk::al {

const char* errorString(ALenum);
std::optional<const char*> getError();

/// Base class for non owning handles to OpenAL objects.
template<ALboolean (*isValid)(ALuint)>
class ObjectHandle
{

    template<class HandleType, void(*Gen)(ALsizei, ALuint*), void(*Del)(ALsizei, const ALuint*)>
    friend class ObjectManager;

public:
    /// Default constructor: id will default to zero, which may or may not be a valid id.
    ObjectHandle() : m_id(0) {}

    /// Checks the handle refers to a valid object of the corresponding type.
    [[nodiscard]] bool valid() const {
        return isValid(m_id);
    }

    [[nodiscard]] explicit operator bool() const {
        return valid();
    }

protected:
    /// Retrieve a property using an alGet... function.
    template<class T, void(*Getter)(ALuint, ALenum, T*)>
    [[nodiscard]] T get(ALenum property) const {
        T value;
        FOLK_AL_CALL(Getter, m_id, property, &value);
        return value;
    }

    template<class T, void(*Setter)(ALuint, ALenum, T)>
    void set(ALenum property, T value) const {
        FOLK_AL_CALL(Setter, m_id, property, value);
    }

    template<class VectorT, auto GetterV>
    VectorT getV(ALenum property) const {
        VectorT vector;
        FOLK_AL_CALL(GetterV, m_id, property, &vector.x);
        return vector;
    }

    template<class VectorT, auto SetterV>
    void setV(ALenum property, const VectorT vector) const {
        FOLK_AL_CALL(SetterV, m_id, property, &vector.x);
    }

    explicit ObjectHandle(ALuint id) : m_id(id) {}

    ALuint m_id {0};
};

/**
 * @brief Base class for OpenAL object managers.
 * A manager differs from
 * @tparam HandleType A subclass of an instantiation of ObjectHandle.
 * @tparam alGen The function to generate new objects of this type (e.g. alGenSources).
 * @tparam alDelete The function to delete objects (e.g. alDeleteSources).
 */
template<class HandleType, void (*alGen)(ALsizei, ALuint*), void (*alDelete)(ALsizei, const ALuint*)>
class ObjectManager : public HandleType {
public:
    /// Creates an OpenAL object.
    ObjectManager() {
        FOLK_AL_CALL(alGen, 1, &id());
    }

    /// Deleted copy constructor.
    ObjectManager(const ObjectManager &) = delete;

    /// Takes ownership of another instance's object.
    ObjectManager(ObjectManager&& other) noexcept {
        id() = other.id();
        other.id() = 0;
    }

    /// Deleted copy assignment.
    ObjectManager& operator=(const ObjectManager&) = delete;

    /// Take ownership of another instance's object.
    ObjectManager& operator=(ObjectManager&& other) noexcept {
        id() = other.id();
        other.id() = 0;
        return *this;
    }

    /// Deletes the managed object.
    ~ObjectManager() {
        if (id() && static_cast<HandleType*>(this)->valid())
            FOLK_AL_CALL(alDelete, 1, &id());
    }

private:
    [[nodiscard]] const ALuint& id() const {
        return static_cast<const HandleType*>(this)->m_id;
    }

    [[nodiscard]] ALuint& id() {
        return static_cast<HandleType*>(this)->m_id;
    }
};

} // namespace Folk::al

#endif // FOLK_AUDIO__OPEN_AL_HPP
