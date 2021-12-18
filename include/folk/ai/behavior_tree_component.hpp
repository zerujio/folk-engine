//
// Created by sergio on 18-12-21.
//

#ifndef INCLUDE_FOLK_AI__BEHAVIOR_TREE_COMPONENT_HPP
#define INCLUDE_FOLK_AI__BEHAVIOR_TREE_COMPONENT_HPP

#include "behavior_tree.hpp"

#include <memory>
#include <functional>

namespace Folk {

    struct BehaviorTreePtr;

    struct BehaviorTreeComponent final {
        using ptr_type = BehaviorTreePtr;
        static constexpr const char* type_name = "BehaviorTree";

        std::unique_ptr<BehaviorTreeInterface> bt;
    };

    struct BehaviorTreePtr final : public ComponentPtr<BehaviorTreeComponent> {
        using ComponentPtr::ComponentPtr;

        /// Cambia el tipo de BehaviorTree asociado y retorna una referencia.
        template<class BT, class... Args>
        BT& setBehaviorTree(Args&&... args) {
            auto ptr = new PolymorphicBT<BT>(std::forward<Args>(args)...);
            ref.bt = std::unique_ptr<PolymorphicBT<BT>>(ptr);
            return ptr->get();
        }
    };

} // namespace Folk

#endif //INCLUDE_FOLK_AI__BEHAVIOR_TREE_COMPONENT_HPP
