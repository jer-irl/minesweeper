#pragma once

#include <vector>

namespace minesweeper {

enum class TileState {
    Normal, Mine, Exploded
};

struct Board;

struct Tile {
public:
    Tile(std::size_t row, std::size_t col, const Board &board);

    std::size_t numNeighboringMines() const;

    void setState(TileState state) {
        state_ = state;
    }

    TileState getState() const {
        return state_;
    }

private:
    const std::size_t row_;
    const std::size_t col_;
    TileState state_;
    const Board &board_;
};

struct Board {
public:
    Board(std::size_t rows, std::size_t cols, std::size_t mines);

    const Tile *tileAt(std::size_t row, std::size_t col) const;
    Tile *tileAt(std::size_t row, std::size_t col);

private:
    std::vector<Tile> tiles_;
    const std::size_t rows_;
    const std::size_t cols_;
};


} // ns minesweeper
