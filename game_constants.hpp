#ifndef GAME_CONSTANTS_HPP
#define GAME_CONSTANTS_HPP

#include <vector>
#include <chrono>

namespace game_constants {
    // !!! min size for with and height = 7 !!!
    constexpr inline int board_height = 15;
    constexpr inline int board_width = 30;

    enum direction { right = 0, up = 1, left = 2, down = 3};

    constexpr int start_size_snake = 2;

    constexpr inline char snake_blocks[] = {'#', 'O', '0', 'o', '@'};

    constexpr inline char empty_boardblock = '.';

    //Wait TIme is number of possible inputs during one "Tick" -> one Tick is Wait Time times factor
    //Standard is 250, 10
    //works with 1000 or 750
    constexpr inline std::chrono::milliseconds tick_duration = std::chrono::milliseconds(150);
    constexpr inline int tick_number = 5; 
}

namespace tetromino_shapes {
    //Tetromino Table angabe von unten rechts nach oben
    //Shape Table Tetromnio 1 -> Square
    const inline std::vector<std::vector<bool>> shape_1 = {{true, true}, {true, true}};        //Normal Rotation
    //Shape Table Tetromino 2 -> small Triangle Block
    const inline std::vector<std::vector<bool>> shape_2 = {{true, true}, {true, false}}; 
    //Shape Table Tetromino 3 -> Small I Block -> First orientation vertical
    const inline std::vector<std::vector<bool>> shape_3 = {{true}, {true}, {true}};
    //Shape Table Tetromino 4 -> Small L Block -> First orientation vertical
    const inline std::vector<std::vector<bool>> shape_4 = {{true, true}, {true}, {true}};
    //Shape Table Tetromino 5 -> Small T Block
    const inline std::vector<std::vector<bool>> shape_5 = {{true, true, true}, {false, true}};

    const inline std::vector<std::vector<std::vector<bool>>> lookup_table_shapes = {shape_1, shape_2, shape_3, shape_4, shape_5};
}


#endif