#include "GameView.hpp"
#include <iostream>
#include <string>

namespace minesweeper {

GameView::GameView(std::size_t rows, std::size_t cols)
        : rows_(rows), cols_(cols) {
    std::cout << '\x1b' << 'Z';
    std::string s;
    std::cin >> s;
    std::cout << s;
}


} // ns minesweeper