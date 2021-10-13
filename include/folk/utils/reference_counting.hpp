#ifndef FOLK_UTILS__REFERENCE_COUNTING_HPP
#define FOLK_UTILS__REFERENCE_COUNTING_HPP

#include<mutex>

namespace Folk {

template<typename T> class Reference;
template<typename T> class ReferenceCountedObject;

/// Pointer-like reference to a reference counted object.
/**
 * Reference-count is incremented by one when this object is constructed, and
 * decreased by one when destroyed. A reference counted object is destroyed when
 * its reference count reaches zero.
*/
template<typename T>
class Reference
{
public:

    /// Construct a reference to an existing object.
    Reference(T*);

    /// Copy-construct a new reference to the same object.
    Reference(Reference const&);

    /// Change the referenced object.
    Reference& operator=(Reference const&);

    /// Destroy reference and decrease reference count of object.
    ~Reference();

    /// Construct a copy of the referenced object and return a reference to it.
    Reference copy();

    T* operator->() const {return _ptr;}

private:
    T* _ptr;
};


/// Utility base class for reference counted objects.
/**
 * Reference counted objects are not meant to be directly instantiated. Classes
 * that inherit from this class should instead provide static methods that
 * return a reference.
 * 
 * ```{c++}
 *  class C : ReferenceCountedObject<int> {
 *  public:
 *      // public methods, no public constructors.
 * 
 *      static Reference<C> createC() { //... }
 * 
 *  private:
 *      // private (or protected) constructors
 *  };
 * 
 *  void main() {
 *      auto c = C::createC();
 *      // use reference ...
 *  }
 * ```
 * 
 * @param <Counter> integer-like type to be used for counting references. Must 
 * implement prefix and postfix increment and decrement operators.
 * @see Reference
*/
template<typename Counter>
class ReferenceCountedObject
{
    template <class T> friend class Reference;

    Counter references {0};

protected:
    ReferenceCountedObject() = default;
};


// DEFINITIONS

/**
 * @param obj a reference counted object.
*/
template<typename T>
Reference<T>::Reference(T* obj) : _ptr(obj) {
    ++(_ptr->references);
}

/**
 * @param ref a reference to a ref-counted object.
 */
template<typename T>
Reference<T>::Reference(Reference const &ref) : _ptr(ref._ptr) {
    ++(_ptr->references);
}

/**
 * @param ref a reference to a ref-counted object.
 */
template<typename T>
Reference<T>& Reference<T>::operator=(Reference const &ref) {
    if (--(_ptr->references) == 0)
        delete _ptr;

    _ptr = ref._ptr;
    ++(ref->references);

    return *this;
}

template<typename T>
Reference<T>::~Reference() {
    if (--(_ptr->references) == 0)
        delete _ptr;
}

template<typename T>
Reference<T> Reference<T>::copy() {
    T *new_obj = new T(*_ptr);

    return Reference(new_obj);
}

}//namespace folk

#endif//FOLK_UTILS__REFERENCE_COUNTING_HPP