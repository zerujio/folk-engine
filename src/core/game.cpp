#include "folk/core/game.hpp"
#include "engine.hpp"

namespace Folk {

void Game::exit() noexcept
{
    Engine::exit_flag = true;
}

void Game::setPerformanceMetricsEnabled(bool value) {
    // TODO: re-implement performance metrics
}

void Game::setWindowTitle(const char* title) {
    Engine::game_window_ptr->setTitle(title);
}

void Game::setMinFrameTime(double time) {
    Engine::min_frame_time = std::chrono::duration_cast<decltype(Engine::min_frame_time)>(std::chrono::duration<double>(time));
}

} // namespace folk