#pragma once

#include "Game.h"

namespace minesweeper {

struct GameView {
public:
    GameView(std::size_t rows, std::size_t cols);

    void drawChar(char c, std::size_t row, std::size_t col) const;
    void drawBorder() const;
    void moveCursorTo(std::size_t row, std::size_t col) const;
    void drawHeader() const;
    void drawPrompt() const;

private:
    std::size_t rows_;
    std::size_t cols_;
};

} // ns minesweeper
