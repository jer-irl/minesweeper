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
                    tile->setDisplayType(DisplayType::Cleared);
                    drawTile(*tile);
                    // TODO: Reveal other tiles
                }
                break;

            default:
                throw std::runtime_error("Unrecognized input character");
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
    switch (tile.getDisplayType()) {
        case DisplayType::Hidden:
            toDraw = 'U';
            break;
        case DisplayType::Exploded:
            toDraw = 'E';
            break;
        case DisplayType::Cleared:
            toDraw = '.';
            break;
        case DisplayType::Displaying:
            toDraw = std::to_string(tile.numNeighboringMines())[0];
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

} // ns minesweeper