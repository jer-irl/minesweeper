#include "Game.hpp"

namespace minesweeper {

Tile::Tile(std::size_t row, std::size_t col, const Board &board)
        : board_(board), row_(row), col_(col), state_(TileState::Normal) {
}

std::size_t Tile::numNeighboringMines() const {
    std::size_t result = 0;

    for (int row = static_cast<int>(row_) - 1; row < row_ + 2; ++row) {
        for (int col = static_cast<int>(col_) - 1; col < col_ + 2; ++col) {
            if (row < 0 || col < 0) {
                continue;
            }
            const Tile *t = board_.tileAt(static_cast<std::size_t>(row), static_cast<std::size_t>(col));
            if (!t || t == this) {
                continue;
            }

            if (t->state_ == TileState::Mine) {
                ++result;
            }
        }
    }

    return result;
}

Board::Board(std::size_t rows, std::size_t cols, std::size_t mines)
        : rows_(rows), cols_(cols) {
    tiles_.reserve(rows * cols);
    for (std::size_t row = 0; row < rows; ++row) {
        for (std::size_t col = 0; col < cols; ++col) {
            tiles_.emplace_back(row, col, *this);
        }
    }

    std::size_t minesGenerated = 0;
    while(minesGenerated < mines) {
        // TODO generate mine
    }
}

const Tile *Board::tileAt(std::size_t row, std::size_t col) const {
    if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
        return nullptr;
    }
    return &tiles_[(row * cols_) + col];
}

Tile *Board::tileAt(std::size_t row, std::size_t col) {
    if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
        return nullptr;
    }
    return &tiles_[(row * cols_) + col];
}

} // ns minesweeper