#include "GameView.hpp"
#include <string>

// TODO
#include <chrono>
#include <thread>

namespace minesweeper {

GameView::GameView(std::size_t rows, std::size_t cols)
        : rows_(rows), cols_(cols) {
    initscr();
    noecho();
    cbreak();

    getmaxyx(stdscr, trows_, tcols_);

    titleBarWin_ = derwin(stdscr, 3, tcols_, 0, 0);
    box(titleBarWin_, 0, 0);
    mvwprintw(titleBarWin_, 1, 1, "HERE");
    wrefresh(titleBarWin_);

    boardWin_ = derwin(stdscr, rows + 2, cols + 2, 5, 0);
    keypad(boardWin_, true);
    box(boardWin_, 0, 0);
    wrefresh(boardWin_);

    moveCurOnBoard(0, 0);
}

GameView::~GameView() {
    delwin(titleBarWin_);
    delwin(boardWin_);
    delwin(promptWin_);
    endwin();
}

int GameView::getInputChar() {
    while (true) {
        int inChar = wgetch(boardWin_);
        switch (inChar) {
            case KEY_LEFT:
                if (curCol_ > 0) {
                    moveCurOnBoard(curRow_, curCol_ - 1);
                }
                break;
            case KEY_UP:
                if (curRow_ > 0) {
                    moveCurOnBoard(curRow_ - 1, curCol_);
                }
                break;
            case KEY_RIGHT:
                if (curCol_ < cols_ - 1) {
                    moveCurOnBoard(curRow_, curCol_ + 1);
                }
                break;
            case KEY_DOWN:
                if (curRow_ < rows_ - 1) {
                    moveCurOnBoard(curRow_ + 1, curCol_);
                }
                break;
            default:
                return inChar;
        }
    }
}

std::tuple<std::size_t, std::size_t> GameView::currentTile() const {
    int x, y;
    getyx(boardWin_, y, x);
    return std::tuple(y - 1, x - 1);
}

void GameView::drawCharOnBoard(char c, std::size_t row, std::size_t col) const {
    mvwaddch(boardWin_, row + 1, col + 1, c);
    wrefresh(boardWin_);
    replaceCurOnBoard();
}

void GameView::moveCurOnBoard(std::size_t row, std::size_t col) {
    curRow_ = row;
    curCol_ = col;
    replaceCurOnBoard();
}

void GameView::replaceCurOnBoard() const {
    wmove(boardWin_, curRow_ + 1, curCol_ + 1);
    wrefresh(boardWin_);
}

} // ns minesweeper