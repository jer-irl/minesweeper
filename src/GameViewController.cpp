#include "GameViewController.hpp"

#include "Game.hpp"
#include "GameView.hpp"

// TODO
#include <thread>
#include <chrono>

namespace minesweeper {

GameViewController::GameViewController(
        minesweeper::Board &board, minesweeper::GameView &gameView, std::size_t rows, std::size_t cols)
        : board_(board), gameView_(gameView), rows_(rows), cols_(cols) {
}

int GameViewController::gameLoop() {
    while (true) {
        int c = gameView_.getInputChar();
        switch (c) {
            case 'q':
                return 0;

            case ' ':
            case '\n':
            case KEY_ENTER:
            case '\r': {
                auto[row, col] = gameView_.currentTile();
                Tile *tile = board_.tileAt(row, col);
                if (!tile) {
                    throw std::exception();
                } else if (tile->getState() == TileType::Mine) {
                    return 1;
                } else if (tile->getState() == TileType::Normal) {
                    return 1;
                }
                break;
            }

            default:
                throw std::exception();
        }
    }

    return 0;
}

void GameViewController::drawBoard() const {
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            const Tile *tile = board_.tileAt(row, col);
            drawTile(*tile);
        }
    }
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