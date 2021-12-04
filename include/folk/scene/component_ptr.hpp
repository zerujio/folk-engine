#ifndef FOLK_SCENE__COMPONENT_HANDLE_HPP
#define FOLK_SCENE__COMPONENT_HANDLE_HPP

#include <entt/entt.hpp>

namespace Folk {

/// _Wrapper_ de un puntero a un componente.
/**
 * ADVERTENCIA: Los punteros a componentes no son estables, por lo que no hay 
 * garantía de que sigan siendo válidos de un cuadro al siguiente (a menos que
 * se estipule expresamente lo contrario). En particular, la eliminación de la 
 * entidad asociada o la eliminación de otro componente del mismo tipo invalidarán
 * punteros y referencias. Por esta razón no es recomendable mantener una 
 * referencia a un componente más allá del alcance de una función.
 * 
 * \param <C> El tipo del componente referenciado.
*/
template<class C>
struct ComponentPtr {

public:
    using component_type = C;

    ComponentPtr(const entt::handle& h) : ref(h.get<C>()) {}

protected:
    friend class Scene;
    C& ref;
};

} // namespace Folk

#endif // FOLK_SCENE__COMPONENT_HANDLE_HPP