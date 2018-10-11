#include "GameView.hpp"
#include <iostream>
#include <string>

namespace minesweeper {

GameView::GameView(std::size_t rows, std::size_t cols)
        : rows_(rows), cols_(cols) {
    auto [trows, tcols] = getTermSize();
    trows_ = trows;
    tcols_ = tcols;

    drawHeader();
    drawBorder();
    drawPrompt();
}

void GameView::sendCSI() const {
    std::cout << '\x1b' << '[';
}

void GameView::sendCUP(std::size_t trow, std::size_t tcol) const {
    sendCSI();
    std::cout << trow << ';' << tcol << 'H';
}

void GameView::sendDSR() const {
    sendCSI();
    std::cout << "6n";
}

std::tuple<std::size_t, std::size_t> GameView::getTermSize() const {
    sendCUP(999, 999);
    sendDSR();

    std::string termResponse;
    std::cin >> termResponse;
    assert(termResponse[0] == '\x1b' && termResponse[1] == '[');

    std::string n;
    char *ptr = &termResponse[2];
    while (*ptr != ';') {
        n += *ptr;
        ++ptr;
    }
    ++ptr;

    std::string m;
    while (*ptr != 'R') {
        m += *ptr;
        ++ptr;
    }

    return std::tuple(std::stoull(n), std::stoll(m));
}

void GameView::moveCursorInTerm(std::size_t trow, std::size_t tcol) const {
    sendCUP(trow, tcol);
}

void GameView::drawCharInTerm(char c, std::size_t trow, std::size_t tcol) const {
    moveCursorInTerm(trow, tcol);
    std::cout << c;
}

void GameView::drawHeader() const {
    moveCursorInTerm(1, 1);
    std::cout << "Welcome to minesweeper!";
}

void GameView::drawPrompt() const {
    moveCursorInTerm(trows_, 1);
    std::cout << "This is the prompt";
}

void GameView::drawBorder() const {
    moveCursorInTerm(3, 1);
    for (std::size_t i = 0; i < cols_ + 2; ++i) {
        std::cout << "-";
    }
    for (std::size_t i = 4; i < rows_ + 4; ++i) {
        moveCursorInTerm(i, 1);
        std::cout << "|";
        // TODO right border
    }
    moveCursorInTerm(rows_ + 4, 1);
    for (std::size_t i = 0; i < cols_ + 2; ++i) {
        std::cout << "-";
    }
}

void GameView::drawCharOnBoard(char c, std::size_t row, std::size_t col) const {
    moveCursorInTerm(row + 3, col + 2);
    std::cout << c;
}

} // ns minesweeper