//
// Created by sergio on 17-12-21.
//

#ifndef INCLUDE_FOLK_AI__BEHAVIOR_TREE_HPP
#define INCLUDE_FOLK_AI__BEHAVIOR_TREE_HPP

#include "folk/scene.hpp"
#include "folk/error.hpp"

#include <chrono>
#include <functional>
#include <tuple>

namespace Folk {

using FloatDelta = std::chrono::duration<float>;

/// Posibles estados de un BehaviorTree
enum class BehaviorTreeStatus {
    /// La ejecución tuvo éxito
    Success,

    /// La ejecución fracasó
    Failure,

    /// La ejecución no terminará en este cuadro
    Running
};

/// Utilizada para BehaviorTree s con polimorfismo dinámico.
/**
 * No es necesario heredar de esta clase para crear un BehaviorTree personalizado, pero todas las instancias de
 * BehaviorTree deben tener una implementación de la función update.
 */
struct BehaviorTreeInterface {

    /// Actualiza el BehaviorTree
    /**
     * @param entity la entidad a la que está asociado este BehaviorTree.
     * @param delta el tie
     * mpo transcurrido entre el inicio de el cuadro anterior y el actual.
     * @return el estado del árbol.
     */
    virtual BehaviorTreeStatus update(EntityHandle entity, FloatDelta delta) = 0;
};

///  BehaviorTree con polimorfismo dinámico
template<class BT>
class PolymorphicBT : public BehaviorTreeInterface {
    BT m_tree;

public:
    template<class... Args>
    PolymorphicBT(Args&&... args) : m_tree(std::forward<Args>(args)...) {}

    BehaviorTreeStatus update(EntityHandle entity, FloatDelta delta) override {
        return m_tree.update(entity, delta);
    }

    [[nodiscard]] BT& get() {
        return m_tree;
    }
};

/// Retorna el resultado de la función predicado
class ConditionBT final {
public:
    using PredicateFunction = std::function<bool(EntityHandle, FloatDelta)>;

    PredicateFunction predicate;

    explicit ConditionBT(PredicateFunction& func) : predicate(func) {}

    BehaviorTreeStatus update(EntityHandle entity, FloatDelta delta) const {
        if (predicate(entity, delta))
            return BehaviorTreeStatus::Success;
        return BehaviorTreeStatus::Failure;
    }
};

/// Ejecuta secuencialmente cada sub-árbol.
/** Equivalente a un AND lógico. Retorna Success si todos los aub-árboles retornan Success. Retorna Running o Failure en
 * cuanto alguno de los sub-árboles retorne Running o Failure, y no ejecuta los siguientes.
 * */
 template <class... Types>
 class SequenceBT final {
 public:
     std::tuple<Types...> sequence;

     /** @param args argumentos que serán utilizados para inicializar la tupla de BTrees.
      */
     template<class... ArgTypes>
     SequenceBT(ArgTypes&&... args) : sequence(std::forward<ArgTypes>(args)...) {}

     BehaviorTreeStatus update(EntityHandle entity, FloatDelta delta) {
         return updateNth<0>(entity, delta);
     }

 private:
     template<std::size_t N>
     BehaviorTreeStatus updateNth(EntityHandle& entity, FloatDelta& delta) {
         if constexpr (N < sizeof...(Types)) {
             auto& bt = std::get<N>(sequence);

             if (bt.update(entity, delta) != BehaviorTreeStatus::Failure)
                 return updateNth<N + 1>();

             return BehaviorTreeStatus::Failure;
         }
         return BehaviorTreeStatus::Success;
     }
 };

 /// Ejecuta secuencialmente cada sub-árbol hasta que uno de ellos retorne Success o Running; retorna Failure si todos fallan.
template<class... Types>
class FallbackBT final {
public:
    std::tuple<Types...> sequence;

    /** @param args argumentos pasados al constructor de la tupla de BTs.
     */
    template<class... ArgTypes>
    FallbackBT(ArgTypes&&... args) : sequence(std::forward<ArgTypes>(args)...) {}

    BehaviorTreeStatus update(EntityHandle entity, FloatDelta delta) {
        return updateNth<0>(entity, delta);
    }

private:
    template<std::size_t N>
    BehaviorTreeStatus updateNth(EntityHandle& entity, FloatDelta& delta) {
        if constexpr (N < sizeof...(Types)) {
            auto& bt = std::get<N>(sequence);
            auto status = bt.update(entity, delta);
            if (status != BehaviorTreeStatus::Failure)
                return status;
            return updateNth<N + 1>(entity, delta);
        }
        return BehaviorTreeStatus ::Failure;
    }
};

} // namespace Folk

#endif //INCLUDE_FOLK_AI__BEHAVIOR_TREE_HPP
