#ifndef FOLK_ENGINE__ENGINE_HPP
#define FOLK_ENGINE__ENGINE_HPP

#include <string>

/// Functions that modify global engine state.
namespace Folk::Engine {

/// Signal the engine to exit (close the application).
void exit();

/// Set the title of the game window.
void setWindowTitle(const char*);

/// Show performance statistics in an ImGUI dialog.
void setPerformanceMetricsEnabled(bool);

} // namespace folk::engine

#endif//FOLK__ENGINE_HPP