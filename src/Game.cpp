#include "Game.hpp"

#include <random>
#include <algorithm>

namespace minesweeper {

Tile::Tile(std::size_t row, std::size_t col, const Board &board)
        : board_(board), row_(row), col_(col), type_(TileType::Normal), displayType_(DisplayType::Hidden) {
}

std::size_t Tile::numNeighboringMines() const {
    std::vector<std::reference_wrapper<const Tile>> neighbors = board_.neighborsForTile(*this);
    return static_cast<std::size_t>(std::count_if(neighbors.begin(), neighbors.end(), [](std::reference_wrapper<const Tile> t){
        return t.get().getType() == TileType::Mine;
    }));
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

std::vector<std::reference_wrapper<Tile>> Board::tilesToRevealOnClick(minesweeper::Tile &tile) {
    std::vector<std::reference_wrapper<Tile>> res;
    tilesToRevealOnClickHelper(tile, res);
    return res;
}

void Board::tilesToRevealOnClickHelper(
        minesweeper::Tile &tile, std::vector<std::reference_wrapper<minesweeper::Tile>> &res) {
    res.emplace_back(tile);

    if (tile.numNeighboringMines() == 0) {
        auto neighbors = neighborsForTile(tile);
        for (Tile &t : neighbors) {
            if (std::none_of(res.begin(), res.end(), [&t](std::reference_wrapper<Tile> s){return &s.get() == &t;})) {
                tilesToRevealOnClickHelper(t, res);
            }
        }
    }
}

std::vector<std::reference_wrapper<Tile>> Board::neighborsForTile(minesweeper::Tile &tile) {
    std::vector<std::reference_wrapper<Tile>> res;

    int tileRow = static_cast<int>(tile.getRow());
    int tileCol = static_cast<int>(tile.getCol());
    for (int row = tileRow - 1; row < tileRow + 2; ++row) {
        for (int col = tileCol - 1; col < tileCol + 2; ++col) {
            Tile *t = tileAt(static_cast<std::size_t>(row), static_cast<std::size_t>(col));

            if (!t || t == &tile) {
                continue;
            }

            res.emplace_back(std::ref(*t));
        }
    }
    return res;
}

std::vector<std::reference_wrapper<const Tile>> Board::neighborsForTile(const minesweeper::Tile &tile) const {
    std::vector<std::reference_wrapper<const Tile>> res;

    int tileRow = static_cast<int>(tile.getRow());
    int tileCol = static_cast<int>(tile.getCol());
    for (int row = tileRow - 1; row < tileRow + 2; ++row) {
        for (int col = tileCol - 1; col < tileCol + 2; ++col) {
            const Tile *t = tileAt(static_cast<std::size_t>(row), static_cast<std::size_t>(col));

            if (!t || t == &tile) {
                continue;
            }

            res.emplace_back(std::ref(*t));
        }
    }
    return res;
}

} // ns minesweeper