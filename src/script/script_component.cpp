//
// Created by sergio on 09-12-21.
//

#include "folk/script/script_component.hpp"

namespace Folk {

    void ScriptPtr::removeScript() const {
        if (ref.script) {
            delete ref.script;
            ref.script = nullptr;
        }
    }

} // namespace Folk