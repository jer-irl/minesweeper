#pragma once

#include <vector>

namespace minesweeper {

enum class TileType {
    Normal, Mine
};

struct Board;

struct Tile {
public:
    Tile(std::size_t row, std::size_t col, const Board &board);

    std::size_t numNeighboringMines() const;

    void setState(TileType state) {
        state_ = state;
    }

    TileType getState() const {
        return state_;
    }

    std::size_t getRow() const {
        return row_;
    }

    std::size_t getCol() const {
        return col_;
    }

private:
    const std::size_t row_;
    const std::size_t col_;
    TileType state_;
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
