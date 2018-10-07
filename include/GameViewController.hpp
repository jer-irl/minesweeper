#pragma once

#include "Game.hpp"
#include "GameView.hpp"

namespace minesweeper {

class GameViewController {
public:
    GameViewController(Board &board, GameView &gameView, std::size_t rows, std::size_t cols);

    int gameLoop();

private:
    Board &board_;
    GameView &gameView_;
    std::size_t rows_;
    std::size_t cols_;
};

} // ns minesweeper
