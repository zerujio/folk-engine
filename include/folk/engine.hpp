#ifndef FOLK__ENGINE_HPP
#define FOLK__ENGINE_HPP

#include <string>

namespace folk::engine {

// Signal the engine to exit (close the application).
void exit();
void setWindowTitle(const char*);

} // namespace folk::engine

#endif//FOLK__ENGINE_HPP