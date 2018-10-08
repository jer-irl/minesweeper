#include "GameViewController.hpp"

namespace minesweeper {

GameViewController::GameViewController(
        minesweeper::Board &board, minesweeper::GameView &gameView, std::size_t rows, std::size_t cols)
        : board_(board), gameView_(gameView), rows_(rows), cols_(cols) {
}

} // ns minesweeper