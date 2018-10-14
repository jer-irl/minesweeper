#pragma once

#include <vector>
#include <functional>

namespace minesweeper {

enum class TileType {
    Normal, Mine
};

enum class DisplayType {
    Exploded, Hidden, Flagged, Cleared
};

struct Board;

struct Tile {
public:
    Tile(std::size_t row, std::size_t col, const Board &board);

    std::size_t numNeighboringMines() const;

    void setType(TileType type) {
        type_ = type;
    }

    TileType getType() const {
        return type_;
    }

    std::size_t getRow() const {
        return row_;
    }

    std::size_t getCol() const {
        return col_;
    }

    void setDisplayType(DisplayType displayType) {
        displayType_ = displayType;
    }

    DisplayType getDisplayType() const {
        return displayType_;
    }

private:
    const std::size_t row_;
    const std::size_t col_;
    TileType type_;
    const Board &board_;
    DisplayType displayType_;
};

struct Board {
public:
    Board(std::size_t rows, std::size_t cols, std::size_t mines);

    const Tile *tileAt(std::size_t row, std::size_t col) const;
    Tile *tileAt(std::size_t row, std::size_t col);

    std::vector<std::reference_wrapper<Tile>> tilesToRevealOnClick(Tile &tile);

    std::vector<std::reference_wrapper<Tile>> neighborsForTile(Tile& tile);
    std::vector<std::reference_wrapper<const Tile>> neighborsForTile(const Tile& tile) const;

private:
    void tilesToRevealOnClickHelper(Tile &tile, std::vector<std::reference_wrapper<Tile>> &res);

    std::vector<Tile> tiles_;
    const std::size_t rows_;
    const std::size_t cols_;
};


} // ns minesweeper
