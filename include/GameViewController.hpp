#pragma once

#include <cstddef>

namespace minesweeper {

struct Board;
struct GameView;

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
