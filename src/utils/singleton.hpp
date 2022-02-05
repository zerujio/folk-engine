#ifndef FOLK_UTILS__SINGLETON_HPP
#define FOLK_UTILS__SINGLETON_HPP

#include "folk/error.hpp"

namespace Folk {

template<typename T>
class Singleton {
    static T* instance_ptr;

public:
    Singleton() {
        if (instance_ptr)
            throw CriticalError("attempted to instantiate a singleton class twice");

        static_assert(std::is_base_of_v<Singleton<T>, T>, "T must inherit from Singleton<T>");
        instance_ptr = static_cast<T*>(this);
    }

    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

    ~Singleton() { instance_ptr = nullptr; }

    /// Access singleton instance.
    static T& instance() {
        [[likely]]
        if (instance_ptr)
            return *instance_ptr;
        throw CriticalError("Singleton class has not been initialized!");
    }
};

template<class T>
T* Singleton<T>::instance_ptr {nullptr};

} // namespace folk

#define FOLK_SINGLETON_CLASS(ClassName) class ClassName : public Singleton<ClassName>
#define FOLK_SINGLETON_CLASS_FINAL(ClassName) class ClassName final : public Singleton<ClassName>

#endif//FOLK_UTILS__SINGLETON_HPP