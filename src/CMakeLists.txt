add_executable(minesweeper
    main.cpp
    Game.cpp
    GameView.cpp
    GameViewController.cpp
    )

target_link_libraries(minesweeper ncurses)