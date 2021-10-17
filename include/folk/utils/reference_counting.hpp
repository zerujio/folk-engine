#ifndef FOLK_UTILS__REFERENCE_COUNTING_HPP
#define FOLK_UTILS__REFERENCE_COUNTING_HPP

#include<mutex>

namespace Folk {

template<typename T> class Reference;
template<typename T> class ReferenceCountedObject;

/// \~spanish Referencia estilo puntero a un objeto con conteo de referencias. \~english Pointer-like reference to a reference counted object.
/**
 * \~spanish
 * El contador de referencias se incrementa en uno cuando se construye este 
 * objeto y se decrementa en uno cuando se destruye. Un objeto con conteo de 
 * referencias es destruido cuando su contador de referencias llega a cero.
 * 
 * \~english
 * Reference-count is incremented by one when this object is constructed, and
 * decreased by one when destroyed. A reference counted object is destroyed when
 * its reference count reaches zero.
*/
template<typename T>
class Reference
{
public:

    /// \~spanish \brief Construye una referencia a un objeto existente.
    /// \~english \brief Construct a reference to an existing object.
    Reference(T*);

    /// \~spanish \brief Construye una nueva referencia al mismo objeto subyacente.
    /// \~english \brief Copy-construct a new reference to the same object.
    Reference(Reference const&);

    /// \~spanish \brief Cambia el objeto al cual se referencia.
    /// \~english \brief Change the referenced object.
    Reference& operator=(Reference const&);

    /// \~spanish \brief Destruye esta referencia, decrementa el contador de referencias.
    /// \~english \brief Destroy reference and decrease reference count of object.
    ~Reference();

    /// \~spanish \brief Construye una copia del objeto subyacente y retorna una referencia.
    /// \~english \brief Construct a copy of the referenced object and return a reference to it.
    Reference copy();

    T* operator->() const {return _ptr;}

private:
    T* _ptr;
};

/// \~spanish \brief Clase base para objetos con conteo de referencias.
/// \~english \brief Utility base class for reference counted objects.
/**
 * \~spanish 
 * Los objetos con conteo de referencias no están pensados para ser instanciados
 * directamente. En su lugar, las clases derivadas implementan métodos estáticos
 * de construcción que retornen una referencia (Reference).
 * 
 * \~english
 * Reference counted objects are not meant to be directly instantiated. Classes
 * that inherit from this class should instead provide static methods that
 * return a reference.
 * 
 * \~
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
 * \~spanish
 * \param <Counter> Tipo entero para contar referencias. Debe implementar los 
 *        operadores de incremento y decremento sufijo y prefijo (`x++`, `++x`, 
 *        `x--`, `--x`).
 * 
 * \~english
 * \param <Counter> integer-like type to be used for counting references. Must 
 * implement prefix and postfix increment and decrement operators.
 * 
 * \~
 * \see Reference
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

template<typename T>
Reference<T>::Reference(T* obj) : _ptr(obj) {
    ++(_ptr->references);
}

template<typename T>
Reference<T>::Reference(Reference const &ref) : _ptr(ref._ptr) {
    ++(_ptr->references);
}

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