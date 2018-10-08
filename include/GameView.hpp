#pragma once

#include <cstddef>

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
    void moveCursorInTerm(std::size_t trow, std::size_t tcol) const;
    void drawCharInTerm(std::size_t trow, std::size_t tcol) const;

    std::size_t rows_;
    std::size_t cols_;
    std::size_t trows_;
    std::size_t tcols_;
};

} // ns minesweeper
