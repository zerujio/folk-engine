#ifndef FOLK_UTILS__OBJECT_POOL_HPP
#define FOLK_UTILS__OBJECT_POOL_HPP

#include <map>
#include <functional>

namespace Folk
{

template <class T>
class ObjectPool {

public:
    using IdIntegerType = unsigned int;
    enum class Id : IdIntegerType {};

    // Construct new object in place, return integer id.
    template<class... Args>
    Id emplace(Arg&&... );

    // Check if an identifier is valid.
    bool valid(const Id) const;

    // Destroy an object
    void destroy(const Id);

    // Access element by Id. Using an invalid identifier results in undefined behaviour.
    T& operator[](const Id);
    T const& operator[](const Id) const;

private:

    IdIntegerType next_id_ {0};
    Id genId() {
        return next_id_++;
    }

    std::map<Id, T> objects_;
};

template <class T>  
template <class... Args>
ObjectPool<T>::Id ObjectPool<T>::emplace(Args&&... args) {
    auto id = genId();
    objects_.emplace(id, std::forward<Args>(args)...);
    return id;
}

template <class T>
bool ObjectPool<T>::valid(const Id) const {
    return objects_.find(Id) != objects_.end();
}

template <class T>
void ObjectPool<T>::destroy(const Id) {
    objects_.erase(Id);
}

template <class T>
T& ObjectPool<T>::operator[](const Id) {
    return objects_.at(Id);
}

template <class T>
T const& ObjectPool<T>::operator[](const Id) const {
    return objects_.at(Id);
}

} // namespace Folk


#endif // FOLK_UTILS__OBJECT_POOL_HPP