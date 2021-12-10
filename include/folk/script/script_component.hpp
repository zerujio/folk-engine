
//
// Created by sergio on 08-12-21.
//

#ifndef FOLK_SCRIPT__SCRIPT_COMPONENT_HPP
#define FOLK_SCRIPT__SCRIPT_COMPONENT_HPP

#include "folk/script/script.hpp"
#include "folk/scene/component_ptr.hpp"

#include <functional>

namespace Folk {

    class ScriptPtr;

    struct ScriptComponent final {
        using ptr_type = ScriptPtr;
        static constexpr const char* type_name = "Script";

        Script* script {nullptr};
        entt::handle handle {};
    };

    class ScriptPtr final : public ComponentPtr<ScriptComponent> {
    public:

        using ComponentPtr::ComponentPtr;

        /// Añade un script. Si ya hay un script asociado, lo quita primero.
        template<class ScriptClass, class... Args>
        ScriptClass& addScript(Args&&...) const;

        /// Quita el script actualmente asociado. No tiene efecto si no hay un script asociado.
        void removeScript() const;

        /// Accede al Script asociado. Retorna un puntero nulo si el tipo de Script es incorrecto.
        template<class ScriptClass>
        ScriptClass* getScript() const;
    };

    template <class ScriptClass, class... Args>
    ScriptClass& ScriptPtr::addScript(Args &&... args) const {
        removeScript();
        auto ptr = new ScriptClass(EntityHandle(ref.handle), std::forward<Args>(args)...);
        ref.script = ptr;
        return *ptr;
    }

    template<class ScriptClass>
    ScriptClass* ScriptPtr::getScript() const {
        return dynamic_cast<ScriptClass*>(ref.script);
    }
} // namespace Folk

#endif //FOLK_SCRIPT__SCRIPT_COMPONENT_HPP
