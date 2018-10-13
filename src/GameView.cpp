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
    keypad(stdscr, true);

    getmaxyx(stdscr, trows_, tcols_);

    titleBarWin_ = derwin(stdscr, 3, tcols_, 0, 0);
    box(titleBarWin_, 0, 0);
    mvwprintw(titleBarWin_, 1, 1, "HERE");
    wrefresh(titleBarWin_);

    boardWin_ = derwin(stdscr, rows + 2, cols + 2, 5, 0);
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
        int inChar = getch();
        switch (inChar) {
            case KEY_LEFT:
                moveCurOnBoard(0, 0);
                // TODO
                break;
            case KEY_UP:
                // TODO
                break;
            case KEY_RIGHT:
                // TODO
                break;
            case KEY_DOWN:
                // TODO
                break;
            default:
                return inChar;
        }
        refresh();
    }
}

std::tuple<std::size_t, std::size_t> GameView::currentTile() const {
    int x, y;
    getyx(boardWin_, y, x);
    return std::tuple(x, y);
}

void GameView::drawCharOnBoard(char c, std::size_t row, std::size_t col) const {
    mvwaddch(boardWin_, row + 1, col + 1, c);
    wrefresh(boardWin_);
    replaceCurOnBoard();
}

void GameView::refreshView() const {
    replaceCurOnBoard();
    refresh();
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