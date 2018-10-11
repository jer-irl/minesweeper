#pragma once

#include <cstddef>
#include <tuple>

namespace minesweeper {

class GameView {
public:
    GameView(std::size_t rows, std::size_t cols);

    std::tuple<std::size_t, std::size_t> getInputSquare() const;

    void drawCharOnBoard(char c, std::size_t row, std::size_t col) const;
    void drawBorder() const;
    void drawHeader() const;
    void drawPrompt() const;

private:
    void moveCursorInTerm(std::size_t trow, std::size_t tcol) const;
    void drawCharInTerm(char c, std::size_t trow, std::size_t tcol) const;
    void sendCSI() const;
    void sendCUP(std::size_t trow, std::size_t tcol) const;
    void sendDSR() const;
    std::tuple<std::size_t, std::size_t> getTermSize() const;

    std::size_t rows_;
    std::size_t cols_;
    std::size_t trows_;
    std::size_t tcols_;
};

} // ns minesweeper
