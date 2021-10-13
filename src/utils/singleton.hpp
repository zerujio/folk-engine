#ifndef FOLK_UTILS__SINGLETON_HPP
#define FOLK_UTILS__SINGLETON_HPP

#include "folk/core/error.hpp"

namespace Folk {

template<typename T>
class Singleton {
public:
    static T& instance() {return *((T*)instance_ptr);}

    Singleton() {
        if (instance_ptr)
            throw CriticalEngineError("attempted to instantiate a singleton class twice");

        instance_ptr = this;
    }

    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

    ~Singleton() noexcept {
        instance_ptr = nullptr;
    }

    operator T*() {return *this;}

private:
    static Singleton<T> *instance_ptr;
};

template<typename T>
Singleton<T>* Singleton<T>::instance_ptr {nullptr};

} // namespace folk

#define FOLK_SINGLETON_CLASS(ClassName) class ClassName : public Singleton<ClassName>
#define FOLK_SINGLETON_CLASS_FINAL(ClassName) class ClassName final : public Singleton<ClassName>

#endif//FOLK_UTILS__SINGLETON_HPP