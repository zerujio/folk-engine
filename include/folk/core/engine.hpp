#ifndef FOLK_ENGINE__ENGINE_HPP
#define FOLK_ENGINE__ENGINE_HPP

#include <string>

namespace Folk::Engine {

/// Signal the engine to exit (close the application).
void exit();

/// Set the title of the game window.
void setWindowTitle(const char*);

} // namespace folk::engine

#endif//FOLK__ENGINE_HPP