#pragma once

#include <cstddef>
#include <tuple>
#include <ncurses.h>

namespace minesweeper {

class GameView {
public:
    GameView(std::size_t rows, std::size_t cols);
    ~GameView();

    std::tuple<std::size_t, std::size_t> getInputSquare() const;

    void drawCharOnBoard(char c, std::size_t row, std::size_t col) const;

private:
    WINDOW *titleBarWin_;
    WINDOW *boardWin_;
    WINDOW *promptWin_;

    std::size_t rows_;
    std::size_t cols_;
    int trows_;
    int tcols_;
};

} // ns minesweeper
