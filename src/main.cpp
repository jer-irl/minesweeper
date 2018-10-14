#include "GameViewController.hpp"
#include "Game.hpp"
#include "GameView.hpp"
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    std::size_t rows = 20;
    std::size_t cols = 40;
    std::size_t mines = 150;
    std::size_t argIdx = 1;

    while (argIdx < argc) {
        std::string arg(argv[argIdx]);
        if (arg == "--rows") {
            ++argIdx;
            rows = std::atoi(argv[argIdx]);
        } else if (arg == "--cols") {
            ++argIdx;
            rows = std::atoi(argv[argIdx]);
        } else if (arg == "--mines") {
            ++argIdx;
            mines = std::atoi(argv[argIdx]);
        } else {
            std::cout << "Bad CLI argument" << std::endl;
            return 1;
        }
        ++argIdx;
    }

    minesweeper::GameView gameView(rows, cols);
    minesweeper::Board board(rows, cols, mines);
    minesweeper::GameViewController controller(board, gameView, rows, cols);

    controller.drawBoard();
    return controller.gameLoop();
}
