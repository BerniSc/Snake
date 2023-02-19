#include "snake_fruit.hpp"

int snake_fruit::fruit_id_counter = 0;

snake_fruit::snake_fruit() : fruit_id(fruit_id_counter++) {

}

snake_fruit::~snake_fruit() {
    std::cout << "destroyed fruit number " << fruit_id << std::endl;
}

void snake_fruit::generate_set_coordinates() {
    int randX = getRandNumber(game_constants::board_width);
    int randY = getRandNumber(game_constants::board_height);

    std::cout << randX << "|" << randY << std::endl;

    snake_fruit::spawn_coordinates.first = randX;
    snake_fruit::spawn_coordinates.second = randY;

    fruit_symbol = 'O';
}

void snake_fruit::drawFruit(char (&board)[game_constants::board_width][game_constants::board_height]) {
    generate_set_coordinates();
    //spawn_coordinates.first = 3;
    //spawn_coordinates.second = 3;
    if(board[spawn_coordinates.first][spawn_coordinates.second] == game_constants::empty_boardblock) {
        board[spawn_coordinates.first][spawn_coordinates.second] = this->fruit_symbol;
    } else {
        generate_set_coordinates();
        drawFruit(board);
    }
}

int snake_fruit::getX() const {
    return this->spawn_coordinates.first;
}

int snake_fruit::getY() const {
    return this->spawn_coordinates.second;
}
