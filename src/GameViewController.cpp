#include "GameViewController.hpp"

#include "Game.hpp"
#include "GameView.hpp"

#include <string>

namespace minesweeper {

GameViewController::GameViewController(
        minesweeper::Board &board, minesweeper::GameView &gameView, std::size_t rows, std::size_t cols)
        : board_(board), gameView_(gameView), rows_(rows), cols_(cols) {
}

int GameViewController::gameLoop() {
    while (true) {
        int c = gameView_.getInputChar();

        auto[row, col] = gameView_.currentTile();
        Tile *tile = board_.tileAt(row, col);

        switch (c) {
            case 'q':
                return 0;

            case 'f':
                tile->setDisplayType(DisplayType::Flagged);
                drawTile(*tile);
                break;

            case ' ':
            case '\n':
            case KEY_ENTER:
            case '\r':
                if (tile->getType() == TileType::Mine) {
                    tile->setDisplayType(DisplayType::Exploded);
                    drawTile(*tile);
                    revealBoard();
                } else if (tile->getType() == TileType::Normal) {
                    clickTile(*tile);
                }
                break;

            default:
                break;
        }
    }
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
    switch (tile.getDisplayType()) {
        case DisplayType::Hidden:
            toDraw = '.';
            break;
        case DisplayType::Exploded:
            toDraw = 'E';
            break;
        case DisplayType::Cleared:
            if (std::size_t neighboring = tile.numNeighboringMines()) {
                toDraw = std::to_string(neighboring)[0];
            } else {
                toDraw = ' ';
            }
            break;
        case DisplayType::Flagged:
            toDraw = 'F';
            break;
    }
    gameView_.drawCharOnBoard(toDraw, tile.getRow(), tile.getCol());
}

void GameViewController::revealBoard() const {
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            const Tile *t = board_.tileAt(row, col);
            if (t->getType() == TileType::Mine && t->getDisplayType() != DisplayType::Exploded) {
                gameView_.drawCharOnBoard('*', row, col);
            }
        }
    }
}

void GameViewController::clickTile(minesweeper::Tile &tile) {
    auto tilesToReveal = board_.tilesToRevealOnClick(tile);
    for (Tile &t : tilesToReveal) {
        t.setDisplayType(DisplayType::Cleared);
        drawTile(t);
    }
}

} // ns minesweeper