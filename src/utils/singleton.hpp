#ifndef FOLK_UTILS__SINGLETON_HPP
#define FOLK_UTILS__SINGLETON_HPP

namespace folk {

template<typename T>
class Singleton {
public:
    static T instance;
protected:
    Singleton() = default;
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;
};

template<typename T>
T Singleton<T>::instance {};

} // namespace folk

#define FOLK_SINGLETON_CLASS(ClassName) class ClassName : public Singleton<ClassName>
#define FOLK_SINGLETON_CLASS_FINAL(ClassName) class ClassName final : public Singleton<ClassName>

#endif//FOLK_UTILS__SINGLETON_HPP