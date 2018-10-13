#pragma once

#include <cstddef>
#include <tuple>
#include <ncurses.h>

namespace minesweeper {

class GameView {
public:
    GameView(std::size_t rows, std::size_t cols);
    ~GameView();

    int getInputChar();
    std::tuple<std::size_t, std::size_t> currentTile() const;

    void drawCharOnBoard(char c, std::size_t row, std::size_t col) const;

private:
    void moveCurOnBoard(std::size_t row, std::size_t col);
    void replaceCurOnBoard() const;

    std::size_t curRow_;
    std::size_t curCol_;

    WINDOW *titleBarWin_;
    WINDOW *boardWin_;
    WINDOW *promptWin_;

    std::size_t rows_;
    std::size_t cols_;
    int trows_;
    int tcols_;
};

} // ns minesweeper
