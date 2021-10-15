#ifndef FOLK_CORE__MODULE_HPP
#define FOLK_CORE__MODULE_HPP

#include "../utils/singleton.hpp"
#include "../utils/update_listener.hpp"

#include <string>

namespace Folk
{

class Module {
public:
    virtual const char* name() const = 0;
};

class UpdateableModule : public Module, public UpdateListener {};

#define FOLK_ENGINE_MODULE(ModuleName) FOLK_SINGLETON_CLASS_FINAL(ModuleName), public Module

#define FOLK_ENGINE_UPDATEABLE_MODULE(ModuleName) FOLK_SINGLETON_CLASS_FINAL(ModuleName), public UpdateableModule

} // namespace Folk


#endif // FOLK_CORE__MODULE_HPP