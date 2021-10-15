#ifndef FOLK_INPUT__MODULE_HPP
#define FOLK_INPUT__MODULE_HPP

#include "../core/module.hpp"

namespace Folk
{
    
FOLK_ENGINE_MODULE(InputModule) {
    InputModule() = default;

public:
    const char* name() const override {return "input_module";}
};

} // namespace folk


#endif // FOLK_INPUT__MODULE_HPP