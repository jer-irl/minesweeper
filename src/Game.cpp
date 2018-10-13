#include "Game.hpp"

#include <random>

namespace minesweeper {

Tile::Tile(std::size_t row, std::size_t col, const Board &board)
        : board_(board), row_(row), col_(col), type_(TileType::Normal), displayType_(DisplayType::Hidden) {
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

            if (t->type_ == TileType::Mine) {
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

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<std::size_t> rowGen(0, rows - 1);
    std::uniform_int_distribution<std::size_t> colGen(0, cols - 1);

    std::size_t minesGenerated = 0;
    while(minesGenerated < mines) {
        std::size_t randRow = rowGen(rng);
        std::size_t randCol = colGen(rng);

        Tile *tile = tileAt(randRow, randCol);

        if (tile->getType() == TileType::Mine) {
            continue;
        }

        tile->setType(TileType::Mine);
        ++minesGenerated;
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