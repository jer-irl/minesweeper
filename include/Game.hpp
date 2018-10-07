#pragma once

#include <vector>

namespace minesweeper {

enum class TileState {
    Normal, Mine, Exploded
};

struct Tile {
public:
    Tile(std::size_t row, std::size_t col);

    std::size_t numNeighboringMines() const;

    void setState(TileState state);
    TileState getState() const;

private:
    std::size_t row_;
    std::size_t col_;
    TileState state_;
};

struct Board {
public:
    Board(std::size_t rows, std::size_t cols, std::size_t mines);

    const std::vector<Tile> &tiles() const;
    Tile &tileAt(std::size_t row, std::size_t col);

private:
    std::vector<Tile> tiles_;
};


} // ns minesweeper
