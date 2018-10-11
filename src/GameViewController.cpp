#include "GameViewController.hpp"

#include "Game.hpp"
#include "GameView.hpp"

namespace minesweeper {

GameViewController::GameViewController(
        minesweeper::Board &board, minesweeper::GameView &gameView, std::size_t rows, std::size_t cols)
        : board_(board), gameView_(gameView), rows_(rows), cols_(cols) {
}

int GameViewController::gameLoop() {
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            const Tile *tile = board_.tileAt(row, col);
            drawTile(*tile);
        }
    }

    // TODO

    return 0;
}

void GameViewController::drawTile(const Tile &tile) const {
    char toDraw;
    switch (tile.getState()) {
        case TileType::Normal:
            toDraw = '.';
            break;
        case TileType::Mine:
            toDraw = 'm';
            break;
    }
    gameView_.drawCharOnBoard(toDraw, tile.getRow(), tile.getCol());
}

} // ns minesweeper